
# WHAT IS WEBSERV  
Webserv is an 42 project, it's a simple http tcp server build with c/cpp, the program aims to teach server socket fundamentals, non blocking, file descriptors monitoring, team collaboration..  
  
### What you can do with this program:  
It's basically an http server, so you can serve files from it, it also runs php cgi, therefore you can show php files contents, and of course you can upload files on the server  and download them
The server accepts 3 methods, GET, POST and DELETE, the server returns responses according to the response state  
  
How to run:  
run ```make``` on terminal, then a webserv executable program will be created then run it like  
```./webserv configfile.conf ``` 

  
  ### Config File
An example of a config file:

```
server

{
		port 8080;
		error 201 ./error_d/403.html;
		error 404 errors/404.html;
		error 405 errors/405.html;
		
		server_name localhost;

		location /
		[
			autoindex      on;
			root           var/www/html/;
			method         GET;
			method         POST;
			cgi_extension .php;
			redirect       https://example.com/;
			body_max_size  1024521;
		]
}
```

in the config file you can include your custome error pages, server_name, and port

#### config location
**autoindex: [on/off]**
generate directory listings for directories that do not have an index file.

**methods :**
to allow a method in the location, you have to write it.

**root :**
root is when the resource are served from.

**cgi_extension :**
to enable the cgi on the location, cgi executes only php files currently

**body_max_size :**
to limit body size by *bytes*.



