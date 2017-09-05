class IServlet {
    virtual bool handleHttpRequest(int client_socket_fd, string req_data) = 0;
};
