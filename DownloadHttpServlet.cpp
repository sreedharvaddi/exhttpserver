class DownloadHttpServlet : public IServlet {
    public bool handleHttpRequest(int client_sd, string req) {
         // process long running operations like send images to client
         return true;
    }
}
