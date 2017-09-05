class Application {
   Application() {
   }
   public void exec() {
       Server server("127.0.0.0", 8080, 6); 
       SimpleHttpServer sample_http_server;
       DownloadHttpServer download_http_server;
       ServletFactory.register("/samplehttpservlet", sample_http_servlet);
       ServletFactory.register("/downloadhttpservlet", download_http_servlet);
       server.start();
       while (true) {
          char str[10];
          cin>>str;
          if (strcmp(str, "quit") {
              return ;
          }
       }
   }

};

int main() {
    Application app;
    app.exec();
}
