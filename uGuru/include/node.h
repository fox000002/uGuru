#ifndef U_NODE_H
#define U_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

struct XNode {
    char ip[15];
    int port;
    char name[256];
};

typedef struct XNode * XNodePtr;


/*! \fn int node_from_string(const char * str, XNodePtr p)
 *  \brief Create nodes from a XML string.
 *  \param str a XML string.
 *  \param p a node.
 *  \return 0 for success, or -1 for fail.
 */
int node_from_string(const char * str, XNodePtr p);


/*! \fn const char * node_to_string(XNodePtr p, char * str)
 *  \brief Convert nodes to a XML string.
 *  \param p a node.
 *  \param str a XML string.
 *  \return str for success, or NULL for fail.
 */
const char * node_to_string(XNodePtr p, char * str);

#ifdef __cplusplus
}
#endif

#endif /* U_NODE_H */
