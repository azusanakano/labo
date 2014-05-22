#ifndef ALTSMTPCLIENT_H
#define ALTSMTPCLIENT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSMTPClient.h
 * \brief   SMTP Client
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altTCPSocket.h>
#include <altBase/altStr.h>
#include <altBase/altLog.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  SMTP Client
///
class altSMTPClient : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altSMTPClient();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSMTPClient();

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
  LIBALT_API alt_t Connect(const altStr & sHost, const altInt nPort = 25);

  ///
  /// \brief  Disconnect
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t Disconnect();

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
  LIBALT_API alt_t SendHELO(const altStr & sSenderHost, altStr & sReplyMessage);

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
  LIBALT_API alt_t SendMailFrom(const altStr & sReversePath, altStr & sReplyMessage);

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
  LIBALT_API alt_t SendRcptTo(const altStr & sForwardPath, altStr & sReplyMessage);

  ///
  /// \brief  Send DATA
  ///
  /// \param  sReplyMessage [ O] Reply message
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_SEND      send error
  /// \return ALT_E_NOMEM     out of memory error
  ///
  LIBALT_API alt_t SendData(altStr & sReplyMessage);

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
  LIBALT_API alt_t SendMailHeader(const altStr & sReversePath, const altStr & sForwardPath, const altStr & sSubject, const altStr & sMailer = "");

  ///
  /// \brief  Send content
  ///
  /// \param  sContent  [I ] content
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_SEND      send error
  ///
  LIBALT_API alt_t SendContent(const altStr & sContent);

  ///
  /// \brief  Send data end
  ///
  /// \param  sReplyMessage [ O] Reply message
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_SEND      send error
  /// \return ALT_E_NOMEM     out of memory error
  ///
  LIBALT_API alt_t SendDataEnd(altStr & sReplyMessage);

  ///
  /// \brief  Send quit
  ///
  /// \param  sReplyMessage [ O] Reply message
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_SEND      send error
  /// \return ALT_E_NOMEM     out of memory error
  ///
  LIBALT_API alt_t SendQuit(altStr & sReplyMessage);

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
  LIBALT_API alt_t SendMail(const altStr & sReversePath, const altStr & sForwardPath, const altStr & sSubject, const altStr & sMessage, const altStr & sMailer = "");

  ///
  /// \brief  Receive reply message
  ///
  /// \param  sReplyMessage [ O] Reply message
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t RecvReply(altStr & sReplyMessage);

protected:
  static const altStr CRLF;

private:
  altTCPSocket  m_oSocket;
};

#endif
