#ifndef U_DOWNLOAD_H
#define U_DOWNLOAD_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*! \fn int download_http_file(const char * host, unsigned int port, const char *rfile, const char *lfile)
 *  \brief Download a file with HTTP.
 *  \param host the host ip.
 *  \param port the host port.
 *  \param rfile a remote file path.
 *  \param lfile a local file path.
 *  \return 0 for success, or -1 for fail.
 */
int download_http_file(const char * host, unsigned int port, const char *rfile, const char *lfile);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* U_DOWNLOAD_H */
