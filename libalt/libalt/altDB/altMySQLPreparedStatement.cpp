/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMySQLPreparedStatement.cpp
 * \brief   MySQL prepared statement class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altMySQLPreparedStatement.h"
#include "altBase/altMem.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  oSQL  [I ] SQL
///
LIBALT_API altMySQLPreparedStatement::altMySQLPreparedStatement(const altSQL & oSQL, altMySQL & oMySQL) : 
altPreparedStatement (oSQL),
m_oMySQL (oMySQL),
m_pQueryBind (NULL),
m_pQueryIsNULL (NULL),
m_pQueryLength (NULL),
m_nParamCount (0),
m_pResultBind (NULL),
m_pResultIsNULL (NULL),
m_pResultLength (NULL),
m_pResultError (NULL),
m_nResultColumnCount (0)
{
}

///
/// \brief  Destructor
///
LIBALT_API altMySQLPreparedStatement::~altMySQLPreparedStatement()
{
  for (altUInt i = 0; i < m_nParamCount; i++) {
    ALT_FREE (m_pQueryBind[i].buffer);
  }
  ALT_FREE (m_pQueryBind);
  ALT_FREE (m_pQueryIsNULL);
  ALT_FREE (m_pQueryLength);
  m_nParamCount = 0;

  for (altUInt i = 0; i < m_nResultColumnCount; i++) {
    ALT_FREE (m_pResultBind[i].buffer);
  }
  ALT_FREE (m_pResultBind);
  ALT_FREE (m_pResultIsNULL);
  ALT_FREE (m_pResultLength);
  ALT_FREE (m_pResultError);
  m_nResultColumnCount = 0;
}

///
/// \brief  Prepare
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_SQL       SQL Error
///
LIBALT_API alt_t altMySQLPreparedStatement::Prepare()
{
  alt_t status;

  try {
    m_oMySQLStmt = m_oMySQL.StmtInit();

    status = m_oMySQLStmt.Prepare (m_oSQL.GetSQL());
    ALT_ERR_RET (status);

    m_oMetaResult = m_oMySQLStmt.ResultMetadata();
  }
  catch(alt_t status) {
    ALT_ERR_RET (status);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Execute
///
/// \param  oResultSet  [ O] Result Set
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_SQL       SQL Error
///
LIBALT_API alt_t altMySQLPreparedStatement::ExcecuteSQL(altDBResultSet & oResultSet)
{
	alt_t status;

	status = BindParam();
	ALT_ERR_RET (status);

  status = m_oMySQLStmt.Execute();
	ALT_ERR_RET (status);

  m_nResultColumnCount = m_oMetaResult.NumFields();
	
	if (m_pResultBind == NULL) {
		status = ALT_MALLOC (m_pResultBind, sizeof (* m_pResultBind) * m_nResultColumnCount);
		ALT_ERR_RET (status);

		if (m_pResultIsNULL == NULL) {
			status = ALT_MALLOC (m_pResultIsNULL, sizeof (* m_pResultIsNULL) * m_nResultColumnCount);
			ALT_ERR_RET (status);
		}

		if (m_pResultLength == NULL) {
			status = ALT_MALLOC (m_pResultLength, sizeof (* m_pResultLength) * m_nResultColumnCount);
			ALT_ERR_RET (status);
		}

		if (m_pResultError == NULL) {
			status = ALT_MALLOC (m_pResultError, sizeof (* m_pResultError) * m_nResultColumnCount);
			ALT_ERR_RET (status);
		}

		altUInt nBufSize = BUFSIZ * 3;
		for (altUInt i = 0; i < m_nResultColumnCount; i++) {
      if (m_oMetaResult.GetMySQLRes()->fields[i].type == MYSQL_TYPE_TINY) {
					m_pResultBind[i].buffer_type = MYSQL_TYPE_TINY;
					status = ALT_MALLOC (m_pResultBind[i].buffer, sizeof (altByte));
					m_pResultLength[i] = sizeof (altByte);
					ALT_ERR_RET (status);
      }
      else if (m_oMetaResult.GetMySQLRes()->fields[i].type == MYSQL_TYPE_SHORT) {
					m_pResultBind[i].buffer_type = MYSQL_TYPE_SHORT;
					status = ALT_MALLOC (m_pResultBind[i].buffer, sizeof (altShort));
					m_pResultLength[i] = sizeof (altShort);
					ALT_ERR_RET (status);
      }
      else if (m_oMetaResult.GetMySQLRes()->fields[i].type == MYSQL_TYPE_LONG) {
					m_pResultBind[i].buffer_type = MYSQL_TYPE_LONG;
					m_pResultBind[i].buffer_length = sizeof (altInt);
					status = ALT_MALLOC (m_pResultBind[i].buffer, sizeof (altInt));
					m_pResultLength[i] = sizeof (altInt);
					ALT_ERR_RET (status);
      }
      else if (m_oMetaResult.GetMySQLRes()->fields[i].type == MYSQL_TYPE_LONGLONG) {
					m_pResultBind[i].buffer_type = MYSQL_TYPE_LONGLONG;
					status = ALT_MALLOC (m_pResultBind[i].buffer, sizeof (altLongLong));
					m_pResultLength[i] = sizeof (altLongLong);
					ALT_ERR_RET (status);
      }
      else if (m_oMetaResult.GetMySQLRes()->fields[i].type == MYSQL_TYPE_FLOAT) {
					m_pResultBind[i].buffer_type = MYSQL_TYPE_FLOAT;
					status = ALT_MALLOC (m_pResultBind[i].buffer, sizeof (altFloat));
					m_pResultLength[i] = sizeof (altFloat);
					ALT_ERR_RET (status);
      }
      else if (m_oMetaResult.GetMySQLRes()->fields[i].type == MYSQL_TYPE_DOUBLE) {
					m_pResultBind[i].buffer_type = MYSQL_TYPE_DOUBLE;
					status = ALT_MALLOC (m_pResultBind[i].buffer, sizeof (altDouble));
					m_pResultLength[i] = sizeof (altDouble);
					ALT_ERR_RET (status);
      }
      else if (m_oMetaResult.GetMySQLRes()->fields[i].type == MYSQL_TYPE_TIME) {
					m_pResultBind[i].buffer_type = MYSQL_TYPE_TIME;
					status = ALT_MALLOC (m_pResultBind[i].buffer, sizeof (MYSQL_TIME));
					m_pResultLength[i] = sizeof (MYSQL_TIME);
					ALT_ERR_RET (status);
      }
      else if (m_oMetaResult.GetMySQLRes()->fields[i].type == MYSQL_TYPE_DATE) {
					m_pResultBind[i].buffer_type = MYSQL_TYPE_DATE;
					status = ALT_MALLOC (m_pResultBind[i].buffer, sizeof (MYSQL_TIME));
					m_pResultLength[i] = sizeof (MYSQL_TIME);
					ALT_ERR_RET (status);
      }
      else if (m_oMetaResult.GetMySQLRes()->fields[i].type == MYSQL_TYPE_DATETIME) {
					m_pResultBind[i].buffer_type = MYSQL_TYPE_DATETIME;
					status = ALT_MALLOC (m_pResultBind[i].buffer, sizeof (MYSQL_TIME));
					m_pResultLength[i] = sizeof (MYSQL_TIME);
					ALT_ERR_RET (status);
      }
      else if (m_oMetaResult.GetMySQLRes()->fields[i].type == MYSQL_TYPE_VAR_STRING) {
					m_pResultBind[i].buffer_type = MYSQL_TYPE_STRING;
					status = ALT_MALLOC (m_pResultBind[i].buffer, nBufSize);
					ALT_ERR_RET (status);
					m_pResultLength[i] = BUFSIZ;
					m_pResultBind[i].buffer_length = (DWORD)nBufSize;
      }
      else if (m_oMetaResult.GetMySQLRes()->fields[i].type == MYSQL_TYPE_BLOB) {
					DWORD nBufferSize = 300 * 1024;
					m_pResultBind[i].buffer_type = MYSQL_TYPE_BLOB;
					status = ALT_MALLOC (m_pResultBind[i].buffer, nBufferSize);
					ALT_ERR_RET (status);
					m_pResultLength[i] = nBufferSize;
					m_pResultBind[i].buffer_length = nBufferSize;
					break;
			}
			m_pResultBind[i].is_null = & m_pResultIsNULL[i];
			m_pResultBind[i].length = & m_pResultLength[i];
			m_pResultBind[i].error = & m_pResultError[i];
		}
	}

  status = m_oMySQLStmt.BindResult (m_pResultBind);
  ALT_ERR_RET (status);

  status = m_oMySQLStmt.StoreResult();
  ALT_ERR_RET (status);

  for (altUInt i = 0; ; i++) {
    status = m_oMySQLStmt.Fetch();
    ALT_ERR_RET (status);
    if (status == ALT_S_NO_DATA) {
      break;
    }

    altDBRow oRow;
    for (altUInt j = 0; j < m_nResultColumnCount; j++) {
      altChar *     pVal = NULL;
      MYSQL_FIELD * pField = m_oMetaResult.FetchFields();

      if (m_pResultIsNULL[j]) {
        oRow.Add (pField[j].name, NULL, 0);
        continue;
      }

      // Time type
      if (m_pResultBind[j].buffer_type == MYSQL_TYPE_TIME
        || m_pResultBind[j].buffer_type == MYSQL_TYPE_DATE
        || m_pResultBind[j].buffer_type == MYSQL_TYPE_DATETIME) {

        MYSQL_TIME * pTime = (MYSQL_TIME *)m_pResultBind[j].buffer;
        altDateTime oTime;

        oTime.m_nYear = pTime->year;
        oTime.m_nMonth = pTime->month;
        oTime.m_nDay = pTime->day;
        oTime.m_nHour = pTime->hour;
        oTime.m_nMin = pTime->minute;
        oTime.m_nSec = pTime->second;

        status = ALT_MALLOC (pVal, sizeof (oTime));
        ALT_ERR_RET (status);
        memcpy (pVal, & oTime, sizeof (oTime));
        oRow.Add (pField[j].name, pVal, sizeof (oTime));
      }
      // String type
      else if (m_pResultBind[j].buffer_type == MYSQL_TYPE_STRING) {
        status = ALT_MALLOC (pVal, m_pResultLength[j] + 2);
        ALT_ERR_RET (status);
        memcpy (pVal, m_pResultBind[j].buffer, m_pResultLength[j]);
        oRow.Add (pField[j].name, pVal, m_pResultLength[j]);
      }
      // etc
      else {
        status = ALT_MALLOC (pVal, m_pResultLength[j]);
        ALT_ERR_RET (status);
        memcpy (pVal, m_pResultBind[j].buffer, m_pResultLength[j]);
        oRow.Add (pField[j].name, pVal, m_pResultLength[j]);
      }
    }
    status = oResultSet.Add (oRow);
    ALT_ERR_RET (status);
  }

  status = Clear();
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Execute
///
/// \param  pAffectedRow  [ O] Affected Count
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_SQL       SQL Error
///
LIBALT_API alt_t altMySQLPreparedStatement::ExcecuteSQL(altULongLong * pAffectedRow)
{
  alt_t status;

  status = BindParam();
  ALT_ERR_RET (status);

  status = m_oMySQLStmt.Execute ();
  ALT_ERR_RET (status);

  if (pAffectedRow != NULL) {
    (* pAffectedRow) = m_oMySQLStmt.AffectedRows();
  }

  status = Clear();
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altChar nVal, const altBool bIsNULL)
{
	alt_t status;

	status = ExntendQueryBuffer();
	ALT_ERR_RET (status);

	m_pQueryIsNULL[m_nParamCount] = bIsNULL;
	m_pQueryBind[m_nParamCount].buffer_type = MYSQL_TYPE_TINY;

	status = ALT_MALLOC (m_pQueryBind[m_nParamCount].buffer, sizeof (altChar));
	ALT_ERR_RET (status);
	memcpy (m_pQueryBind[m_nParamCount].buffer, & nVal, sizeof (altChar));
	m_pQueryBind[m_nParamCount].buffer_length = sizeof (altChar);

	m_nParamCount++;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altByte nVal, const altBool bIsNULL)
{
  alt_t status;

  status = Add (static_cast<altChar>(nVal), bIsNULL);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altShort nVal, const altBool bIsNULL)
{
	alt_t status;

	status = ExntendQueryBuffer();
	ALT_ERR_RET (status);

	m_pQueryIsNULL[m_nParamCount] = bIsNULL;
	m_pQueryBind[m_nParamCount].buffer_type = MYSQL_TYPE_SHORT;
	status = ALT_MALLOC (m_pQueryBind[m_nParamCount].buffer, sizeof (altShort));
	ALT_ERR_RET (status);
	memcpy (m_pQueryBind[m_nParamCount].buffer, & nVal, sizeof (altShort));
	m_pQueryBind[m_nParamCount].buffer_length = sizeof (altShort);

	m_nParamCount++;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altUShort nVal, const altBool bIsNULL)
{
  alt_t status;

  status = Add (static_cast<altShort>(nVal), bIsNULL);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altInt nVal, const altBool bIsNULL)
{
  alt_t status;

  status = ExntendQueryBuffer();
  ALT_ERR_RET (status);

  m_pQueryIsNULL[m_nParamCount] = bIsNULL;
  m_pQueryBind[m_nParamCount].buffer_type = MYSQL_TYPE_LONG;
  status = ALT_MALLOC (m_pQueryBind[m_nParamCount].buffer, sizeof (altInt));
  ALT_ERR_RET (status);
  memcpy (m_pQueryBind[m_nParamCount].buffer, & nVal, sizeof (altInt));
  m_pQueryBind[m_nParamCount].buffer_length = sizeof (altInt);

  m_nParamCount++;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altUInt nVal, const altBool bIsNULL)
{
  alt_t status;

  status = Add (static_cast<altInt>(nVal), bIsNULL);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altLong nVal, const altBool bIsNULL)
{
  alt_t status;

  status = Add (static_cast<altInt>(nVal), bIsNULL);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altULong nVal, const altBool bIsNULL)
{
  alt_t status;

  status = Add (static_cast<altInt>(nVal), bIsNULL);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altLongLong nVal, const altBool bIsNULL)
{
	alt_t status;

	status = ExntendQueryBuffer();
	ALT_ERR_RET (status);

	m_pQueryIsNULL[m_nParamCount] = bIsNULL;
	m_pQueryBind[m_nParamCount].buffer_type = MYSQL_TYPE_LONGLONG;
	status = ALT_MALLOC (m_pQueryBind[m_nParamCount].buffer, sizeof (altLongLong));
	ALT_ERR_RET (status);
	memcpy (m_pQueryBind[m_nParamCount].buffer, & nVal, sizeof (altLongLong));
	m_pQueryBind[m_nParamCount].buffer_length = sizeof (altLongLong);

	m_nParamCount++;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altULongLong nVal, const altBool bIsNULL)
{
  alt_t status = Add (static_cast<altLongLong>(nVal), bIsNULL);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altFloat nVal, const altBool bIsNULL)
{
	alt_t status;

	status = ExntendQueryBuffer();
	ALT_ERR_RET (status);

	m_pQueryIsNULL[m_nParamCount] = bIsNULL;
	m_pQueryBind[m_nParamCount].buffer_type = MYSQL_TYPE_FLOAT;
	status = ALT_MALLOC (m_pQueryBind[m_nParamCount].buffer, sizeof (altFloat));
	ALT_ERR_RET (status);
	memcpy (m_pQueryBind[m_nParamCount].buffer, & nVal, sizeof (altFloat));
	m_pQueryBind[m_nParamCount].buffer_length = sizeof (altFloat);

	m_nParamCount++;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  nVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altDouble nVal, const altBool bIsNULL)
{
	alt_t status;

	status = ExntendQueryBuffer();
	ALT_ERR_RET (status);

	m_pQueryIsNULL[m_nParamCount] = bIsNULL;
	m_pQueryBind[m_nParamCount].buffer_type = MYSQL_TYPE_DOUBLE;
	status = ALT_MALLOC (m_pQueryBind[m_nParamCount].buffer, sizeof (altDouble));
	ALT_ERR_RET (status);
	memcpy (m_pQueryBind[m_nParamCount].buffer, & nVal, sizeof (altDouble));
	m_pQueryBind[m_nParamCount].buffer_length = sizeof (altDouble);

	m_nParamCount++;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  sVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altStr & sVal, const altBool bIsNULL)
{
	alt_t status;

	status = ExntendQueryBuffer();
	ALT_ERR_RET (status);

	m_pQueryBind[m_nParamCount].buffer_type = MYSQL_TYPE_STRING;

  status = ALT_MALLOC (m_pQueryBind[m_nParamCount].buffer, sVal.GetLen() + 1);
	ALT_ERR_RET (status);
  memcpy (m_pQueryBind[m_nParamCount].buffer, sVal.GetCStr(), sVal.GetLen());
	m_pQueryBind[m_nParamCount].buffer_length = static_cast<DWORD>(sVal.GetLen() + 1);

	m_pQueryIsNULL[m_nParamCount] = bIsNULL;
  m_pQueryLength[m_nParamCount] = static_cast<DWORD>(sVal.GetLen());

	m_nParamCount++;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Value
///
/// \param  oVal    [I ] Value
/// \param  bIsNULL [I ] true...null false...not null
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altMySQLPreparedStatement::Add(const altDateTime & oVal, const altBool bIsNULL)
{
	alt_t status;

	status = ExntendQueryBuffer();
	ALT_ERR_RET (status);

	m_pQueryBind[m_nParamCount].buffer_type = MYSQL_TYPE_DATETIME;

	status = ALT_MALLOC (m_pQueryBind[m_nParamCount].buffer, sizeof (MYSQL_TIME));
	ALT_ERR_RET (status);
	
	MYSQL_TIME oTime;
	memset (& oTime, 0x00, sizeof (oTime));
	oTime.year = oVal.m_nYear;
	oTime.month = oVal.m_nMonth;
	oTime.day = oVal.m_nDay;
	oTime.hour = oVal.m_nHour;
	oTime.minute = oVal.m_nMin;
	oTime.second = oVal.m_nSec;

	memcpy (m_pQueryBind[m_nParamCount].buffer, & oTime, sizeof (oTime));
	m_pQueryBind[m_nParamCount].buffer_length = sizeof (oTime);

	m_pQueryIsNULL[m_nParamCount] = bIsNULL;

	m_nParamCount++;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Clear Query Parameter
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altMySQLPreparedStatement::Clear()
{
  for (altUInt i = 0; i < m_nParamCount; i++) {
    ALT_FREE (m_pQueryBind[i].buffer);
  }
  ALT_FREE (m_pQueryBind);
  ALT_FREE (m_pQueryIsNULL);
  ALT_FREE (m_pQueryLength);
  m_nParamCount = 0;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get SQL String
///
/// \return SQL String
///
LIBALT_API altStr altMySQLPreparedStatement::toString() const
{
  altStr  sSQL = m_oSQL.GetSQL();
	for (altUInt i = 0; m_nParamCount; i++) {
    altInt nIndex = sSQL.Find("?");
    if (nIndex < 0) {
      break;
    }
		MYSQL_TIME *  pTime = NULL;
		altByte       nByte = 0;
		altShort      nShort = 0;
		altInt        nInt = 0;
		altLongLong   nLongLong = 0;
		altFloat      fFloat = 0;
		altDouble     fDouble = 0;
    altStr        sVal;
    if (m_pQueryBind[i].buffer_type == MYSQL_TYPE_TINY) {
      memcpy (& nByte, m_pQueryBind[i].buffer, sizeof (nByte));
      sSQL.Replace ("?", sVal.Format ("%u", nByte));
    }
    else if (m_pQueryBind[i].buffer_type == MYSQL_TYPE_SHORT) {
					memcpy (& nShort, m_pQueryBind[i].buffer, sizeof (nShort));
          sSQL.Replace ("?", sVal.Format ("%u", nShort));
    }
    else if (m_pQueryBind[i].buffer_type == MYSQL_TYPE_LONG) {
					memcpy (& nInt, m_pQueryBind[i].buffer, sizeof (nInt));
          sSQL.Replace ("?", sVal.Format ("%u", nInt));
    }
    else if (m_pQueryBind[i].buffer_type == MYSQL_TYPE_LONGLONG) {
					memcpy (& nLongLong, m_pQueryBind[i].buffer, sizeof (nLongLong));
          sSQL.Replace ("?", sVal.Format ("%lu", nLongLong));
    }
    else if (m_pQueryBind[i].buffer_type == MYSQL_TYPE_FLOAT) {
					memcpy (& fFloat, m_pQueryBind[i].buffer, sizeof (fFloat));
          sSQL.Replace ("?", sVal.Format ("%f", fFloat));
    }
    else if (m_pQueryBind[i].buffer_type == MYSQL_TYPE_DOUBLE) {
					memcpy (& fDouble, m_pQueryBind[i].buffer, sizeof (fDouble));
          sSQL.Replace ("?", sVal.Format ("%f", fDouble));
    }
    else if (m_pQueryBind[i].buffer_type == MYSQL_TYPE_TIME) {
					pTime = (MYSQL_TIME *)m_pQueryBind[i].buffer;
          sSQL.Replace ("?", sVal.Format ("'%02d:%02d:%02d'", pTime->hour, pTime->minute, pTime->second));
    }
    else if (m_pQueryBind[i].buffer_type == MYSQL_TYPE_DATE) {
					pTime = (MYSQL_TIME *)m_pQueryBind[i].buffer;
          sSQL.Replace ("?", sVal.Format ("%04d-%02d-%02d'", pTime->year, pTime->month, pTime->day));
    }
    else if (m_pQueryBind[i].buffer_type == MYSQL_TYPE_DATETIME) {
					pTime = (MYSQL_TIME *)m_pQueryBind[i].buffer;
          sSQL.Replace ("?", sVal.Format ("'%04d-%02d-%02d %02d:%02d:%02d'", pTime->year, pTime->month, pTime->day, pTime->hour, pTime->minute, pTime->second));
    }
    else if (m_pQueryBind[i].buffer_type == MYSQL_TYPE_STRING) {
          sSQL.Replace ("?", sVal.Format ("'%s'", m_pQueryBind[i].buffer));
    }
    else if (m_pQueryBind[i].buffer_type == MYSQL_TYPE_BLOB) {
					break;
		}
	}
  return (sSQL);
}

///
/// \brief	Extend Query Buffer
///
/// \return ALT_S_SUCCESS	Success
/// \return ALT_E_NOMEM		Out of Memory
///
alt_t altMySQLPreparedStatement::ExntendQueryBuffer()
{
  alt_t status;

	altUInt nNowSize = sizeof (* m_pQueryBind) * (m_nParamCount + 0);
	altUInt nNewSize = sizeof (* m_pQueryBind) * (m_nParamCount + 1);

	status = ALT_EXALLOC (m_pQueryBind, nNowSize, nNewSize);
	ALT_ERR_RET (status);

	nNowSize = sizeof (* m_pQueryIsNULL) * (m_nParamCount + 0);
	nNewSize = sizeof (* m_pQueryIsNULL) * (m_nParamCount + 1);
	status = ALT_EXALLOC (m_pQueryIsNULL, nNowSize, nNewSize);
	ALT_ERR_RET (status);

	nNowSize = sizeof (* m_pQueryLength) * (m_nParamCount + 0);
	nNewSize = sizeof (* m_pQueryLength) * (m_nParamCount + 1);
	status = ALT_EXALLOC (m_pQueryLength, nNowSize, nNewSize);
	ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief	Bind Query Buffer
///
/// \return ALT_S_SUCCESS Success
/// \return ALT_E_ERROR   SQL Error
///
alt_t altMySQLPreparedStatement::BindParam()
{
	if (m_pQueryBind != NULL) {
		for (altUInt i = 0; i < m_nParamCount; i++) {
			if (m_pQueryIsNULL[i]) {
				m_pQueryBind[i].is_null = & m_pQueryIsNULL[i];
			}
			else {
				m_pQueryBind[i].is_null = NULL;
			}
			m_pQueryBind[i].length = & m_pQueryLength[i];
		}
    alt_t status = m_oMySQLStmt.BindParam (m_pQueryBind);
    ALT_ERR_RET (status);
	}

  ALT_RET (ALT_S_SUCCESS);
}


