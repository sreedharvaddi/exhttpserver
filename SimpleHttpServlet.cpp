class HelloHttpServlet : public IServlet {
    public bool handleHttpRequest(int client_sd, string request) {
        char hello = " I am Hello Http Servlet ";
        send(client_sd, hello, strlen(hello), 0);
    }
};
