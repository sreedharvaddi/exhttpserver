class ServletFactory {
   static map<string, IServlet> url_servlet_mapping;
   
   public static bool register(string url_pattern, IServlet servlet) {
       if (url_servlet_map.find(url_pattern) == url_servlet_map.end()) {
           url_servlet_map.insert(make_pair(url_pattern, servlet));
           return true;
       }
       printf("%s pattern is already registered", url_pattern);
       return false;
   }
   public static bool deregister(string url_pattern) {
       if (url_servlet_map.find(url_pattern) == url_servlet_map.end()) {
           url_servlet.remove(url_pattern);
           return true;
       }
       printf("%s pattern not found to deregister", url_pattern);
       return false;
   }
   public static getServlet(string url_pattern) {
       map<string, IServlet>::iterator it = url_servlet_mapping.find(url_pattern);
       if (it != url_servlet_mapping.end()) {
           return it->second();
       }
       return null;
   }
}
