#ifndef U_REQUEST_H
#define  U_REQUEST_H

/*! \fn void fetch_server_info(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /server_info.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void fetch_server_info(struct mg_connection *conn, const struct mg_request_info *ri);

/*! \fn void fetch_server_state(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /server_state.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void fetch_server_state(struct mg_connection *conn, const struct mg_request_info *ri);

/*! \fn void submit_task(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /submit.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void submit_task(struct mg_connection *conn, const struct mg_request_info *ri);

/*! \fn void query_running_data(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /query.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void query_running_data(struct mg_connection *conn, const struct mg_request_info *ri);

/*! \fn void force_terminate(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /terminate.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void force_terminate(struct mg_connection *conn, const struct mg_request_info *ri);

/*! \fn void show_homepage(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void show_homepage(struct mg_connection *conn, const struct mg_request_info *ri);

/*! \fn void upload_file(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /upload.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void upload_file(struct mg_connection *conn, const struct mg_request_info *ri);

/*! \fn void download_file(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /download.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void download_file(struct mg_connection *conn, const struct mg_request_info *ri);

/*! \fn void start_processing(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /start.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void start_processing(struct mg_connection *conn, const struct mg_request_info *ri);

/*! \fn void debug_info(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /start.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void debug_info(struct mg_connection *conn, const struct mg_request_info *ri);

/*! \fn void prepare_files(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /start.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void prepare_files(struct mg_connection *conn, const struct mg_request_info *ri);

/*! \fn void prepare_files(struct mg_connection *conn, const struct mg_request_info *ri)
 *  \brief Request callback for /start.
 *  \param conn mg_connection.
 *  \param ri mg_request_info.
 */
void new_taskid(struct mg_connection *conn, const struct mg_request_info *ri);

#endif /* U_REQUEST_H */
