/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSMTPClient.cpp
 * \brief   SMTP Client
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSMTPClient.h"
#include "altNetUtil.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/
const altStr altSMTPClient::CRLF = "\r\n";

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altSMTPClient::altSMTPClient() :
m_oSocket()
{
}

///
/// \brief  Destructor
///
LIBALT_API altSMTPClient::~altSMTPClient()
{
  alt_t status = Disconnect();
  ALT_LOG (status);
}

///
/// \brief  Connect
///
/// \param  sHost [I ] Host name
/// \param  nPort [I ] Port number
///
/// \return ALT_S_SUCCESS       success
/// \retrun ALT_E_CONNECT       connect error
/// \return	ALT_E_SOCKET        create socket error
/// \return ALT_E_UNKOWN_HOST   unknown host error
///
LIBALT_API alt_t altSMTPClient::Connect(const altStr & sHost, const altInt nPort)
{
  alt_t status;

  status = m_oSocket.Connect (sHost, nPort);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Disconnect
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altSMTPClient::Disconnect()
{
  alt_t status;
  status = m_oSocket.Disconnect();
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send HELO
///
/// \param  sSenderHost   [I ] Sender host
/// \param  sReplyMessage [ O] Reply message
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_SEND      send error
/// \return ALT_E_NOMEM     out of memory error
///
LIBALT_API alt_t altSMTPClient::SendHELO(const altStr & sSenderHost, altStr & sReplyMessage)
{
  alt_t   status;
  altStr  sBuf;

  sBuf.Format ("HELO %s%s", sSenderHost.GetCStr(), CRLF.GetCStr());

  status = m_oSocket.Send (sBuf.GetCStr(), sBuf.GetLen());
  ALT_ERR_RET (status);

  altStr  sReply;
  status = RecvReply (sReply);
  ALT_ERR_RET (status);
  sReplyMessage += sReply;
  
  status = RecvReply (sReply);
  ALT_ERR_RET (status);
  sReplyMessage += sReply;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send Mail From
///
/// \param  sReversePath  [I ] Reverse Path
/// \param  sReplyMessage [ O] Reply message
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_SEND      send error
/// \return ALT_E_NOMEM     out of memory error
///
LIBALT_API alt_t altSMTPClient::SendMailFrom(const altStr & sReversePath, altStr & sReplyMessage)
{
  alt_t   status;
  altStr  sBuf;

  sBuf.Format ("MAIL FROM:<%s>%s", sReversePath.GetCStr(), CRLF.GetCStr());

  status = m_oSocket.Send (sBuf.GetCStr(), sBuf.GetLen());
  ALT_ERR_RET (status);

  status = RecvReply (sReplyMessage);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send RCPT TO
///
/// \param  sForwardPath  [I ] Forward path
/// \param  sReplyMessage [ O] Reply message
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_SEND      send error
/// \return ALT_E_NOMEM     out of memory error
///
LIBALT_API alt_t altSMTPClient::SendRcptTo(const altStr & sForwardPath, altStr & sReplyMessage)
{
  alt_t   status;
  altStr  sBuf;

  sBuf.Format ("RCPT TO:<%s>%s", sForwardPath.GetCStr(), CRLF.GetCStr());

  status = m_oSocket.Send (sBuf.GetCStr(), sBuf.GetLen());
  ALT_ERR_RET (status);

  status = RecvReply (sReplyMessage);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send DATA
///
/// \param  sReplyMessage [ O] Reply message
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_SEND      send error
/// \return ALT_E_NOMEM     out of memory error
///
LIBALT_API alt_t altSMTPClient::SendData(altStr & sReplyMessage)
{
  alt_t   status;
  altStr  sBuf;

  sBuf.Format ("DATA %s", CRLF.GetCStr());

  status = m_oSocket.Send (sBuf.GetCStr(), sBuf.GetLen());
  ALT_ERR_RET (status);

  status = RecvReply (sReplyMessage);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send mail header
///
/// \param  sReversePath  [I ] Reverse path
/// \param  sForwardPath  [I ] Forward path
/// \param  sSubject      [I ] Subject
/// \param  sMailer       [I ] Mailer
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_SEND      send error
///
LIBALT_API alt_t altSMTPClient::SendMailHeader(const altStr & sReversePath, const altStr & sForwardPath, const altStr & sSubject, const altStr & sMailer)
{
  alt_t   status;
  altStr  sBuf;

  sBuf.Format ("From: %s%s", sReversePath.GetCStr(), CRLF.GetCStr());
  status = m_oSocket.Send (sBuf.GetCStr(), sBuf.GetLen());
  ALT_ERR_RET (status);

  sBuf.Format ("To: %s%s", sForwardPath.GetCStr(), CRLF.GetCStr());
  status = m_oSocket.Send (sBuf.GetCStr(), sBuf.GetLen());
  ALT_ERR_RET (status);

  sBuf.Format ("Subject: %s%s", sSubject.GetCStr(), CRLF.GetCStr());
  status = m_oSocket.Send (sBuf.GetCStr(), sBuf.GetLen());
  ALT_ERR_RET (status);

  sBuf.Format ("X-Mailer: %s%s%s", sSubject.GetCStr(), CRLF.GetCStr(), CRLF.GetCStr());
  status = m_oSocket.Send (sBuf.GetCStr(), sBuf.GetLen());
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send content
///
/// \param  sContent  [I ] content
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_SEND      send error
///
LIBALT_API alt_t altSMTPClient::SendContent(const altStr & sContent)
{
  alt_t   status;
  altStr  sTmp = sContent;

  sTmp.Replace ("\r\n.\r\n", "\r\n..\r\n");

  status = m_oSocket.Send (sTmp.GetCStr(), sTmp.GetLen());
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send data end
///
/// \param  sReplyMessage [ O] Reply message
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_SEND      send error
/// \return ALT_E_NOMEM     out of memory error
///
LIBALT_API alt_t altSMTPClient::SendDataEnd(altStr & sReplyMessage)
{
  alt_t   status;
  altStr  sBuf;

  sBuf.Format ("%s.%s", CRLF.GetCStr(), CRLF.GetCStr());
  status = m_oSocket.Send (sBuf.GetCStr(), sBuf.GetLen());
  ALT_ERR_RET (status);
  
  status = RecvReply (sReplyMessage);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send quit
///
/// \param  sReplyMessage [ O] Reply message
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_SEND      send error
/// \return ALT_E_NOMEM     out of memory error
///
LIBALT_API alt_t altSMTPClient::SendQuit(altStr & sReplyMessage)
{
  alt_t   status;
  altStr  sBuf;

  sBuf.Format ("QUIT %s", CRLF.GetCStr());
  status = m_oSocket.Send (sBuf.GetCStr(), sBuf.GetLen());
  ALT_ERR_RET (status);
  
  status = RecvReply (sReplyMessage);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send Mail
///
/// \param  sReversePath  [I ] Reverse path
/// \param  sForwardPath  [I ] Forward path
/// \param  sSubject      [I ] Subject
/// \param  sMessage      [I ] Message
/// \param  sMailer       [I ] Mailer
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_SEND      send error
/// \return ALT_E_NOMEM     out of memory error
///
LIBALT_API alt_t altSMTPClient::SendMail(const altStr & sReversePath, const altStr & sForwardPath, const altStr & sSubject, const altStr & sMessage, const altStr & sMailer)
{
  alt_t   status;
  altStr  sReply;
  altStr  sHost;

  status = altNetUtil::GetLocalHostName (sHost);
  ALT_ERR_RET (status);

  status = SendHELO (sHost, sReply);
  ALT_ERR_RET (status);

  status = SendMailFrom (sReversePath, sReply);
  ALT_ERR_RET (status);

  status = SendRcptTo (sForwardPath, sReply);
  ALT_ERR_RET (status);

  status = SendData (sReply);
  ALT_ERR_RET (status);

  status = SendMailHeader (sReversePath, sForwardPath, sSubject, sMailer);
  ALT_ERR_RET (status);

  status = SendContent (sMessage);
  ALT_ERR_RET (status);

  status = SendDataEnd (sReply);
  ALT_ERR_RET (status);

  status = SendQuit (sReply);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Receive reply message
///
/// \param  sReplyMessage [ O] Reply message
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory error
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altSMTPClient::RecvReply(altStr & sReplyMessage)
{
  alt_t       status;
  altCharPtr  pBuf;
  altUInt     nSize = ALT_BUFSIZ;

  status = m_oSocket.Recv (pBuf, nSize);
  ALT_ERR_RET (status);

  sReplyMessage = (altChar *)pBuf;

  ALT_RET (ALT_S_SUCCESS);
}
