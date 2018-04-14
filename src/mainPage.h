#ifndef _ARDUINO
#include <Arduino.h>
#define _ARDUINO
#endif

String mainPage = "\
<!doctype html>\
<html>\
<head>\
  <meta name=\"author\" content=\"nicioniz\">\
  <meta name=\"description\" content=\"A simple page that controls a Wemos D1 Mini with an IR transmitter\">\
  <title>Sony TV Remote</title>\
  <meta charset=\"unicode\">\
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
  <!-- Bootstrap CSS -->\
  <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css\" integrity=\"sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm\" crossorigin=\"anonymous\">\
  <link href=\"//netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap-glyphicons.css\" rel=\"stylesheet\">\
  <style type=\"text/css\">\
			.myButton {\
				outline: none;\
				cursor: pointer;\
				text-align: center;\
				text-decoration: none;\
				font: bold 12px Arial, Helvetica, sans-serif;\
				color: #FFFFFF;\
				padding: 10px 20px;\
				border: solid 1px #0076A3;\
			}\
			.green {\
				background: #73B10E;\
			}\
			.black {\
				background: #000000;\
			}\
			.red {\
				background: #FF0000;\
			}\
			.green2 {\
				background: #00FF00;\
			}\
			.yellow {\
				background: #FFFF00;\
			}\
			.blue {\
				background: #0000FF;\
			}\
			.white {\
				color: #FFFFFF;\
			}\
	</style>\
  <script>\
    function myGetXmlHttpRequest() {\
      var xhr = false, activeXoptions = new Array(\"Microsoft.XmlHttp\", \"MSXML4.XmlHttp\", \"MSXML3.XmlHttp\", \"MSXML2.XmlHttp\", \"MSXML.XmlHttp\" );\
      try { \
        xhr = new XMLHttpRequest(); \
      } \
      catch (e) {\
      }\
      if ( ! xhr ) {\
        var created = false; \
        for ( var i = 0 ; i < activeXoptions.length && !created ; i++ ) {\
          try {\
            xhr = new ActiveXObject( activeXoptions[i] );\
            created = true;\
          } \
          catch (e) { \
          } \
        }\
      }\
      return xhr;\
    }\
    \
    function callback(theXhr, target) {\
      if (theXhr.readyState === 4) {\
        if (theXhr.status === 200) {\
\
}\
}\
}\
\
    function doAJAX(uri, target, xhr) {\
      xhr.onreadystatechange = function() {\
        callback(xhr, target);\
      };\
      try {\
        xhr.open(\"put\", uri, true);\
      } catch (e) {\
        alert(e);\
      }\
      xhr.setRequestHeader(\"connection\", \"close\");\
      xhr.send(null);\
    }\
    \
    function do(uri, target) {\
      var xhr = myGetXmlHttpRequest();\
      if (xhr)\
        doAJAX(uri, target, xhr);\
    }\
  </script>\
</head>\
<body>\
\
<div class=\"container-fluid\">\
	<div class=\"row\">\
		<div class=\"col-4 align-items-center\">\
			 <button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/input',document)\">Input</button>\
		</div>\
		<div class=\"col-4 align-items-center\"></div>\
		<div class=\"col-4 align-items-center\">\
			 <button class=\"myButton green text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/onoff',document)\"><span class=\"glyphicon glyphicon-off\"></button>\
		</div>\
	</div>\
	\
	<br/><br/>\
	\
	<div class=\"row\">\
		<div class=\"col-3 align-items-center\">\
			 <button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/andig',document)\">Analog/Digital</button>\
		</div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/audio',document)\">Audio</button>\
		</div>\
		<div class=\"col-3 align-items-center\"></div>\
		<div class=\"col-3 align-items-center\">\
			 <button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/sync',document)\">Sync</button>\
		</div>\
	</div>\
\
	<br/><br/>\
	\
	<div class=\"row\">\
		<div class=\"col-4 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/1',document)\">1</button>\
		</div>\
		<div class=\"col-4 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/2',document)\">2</button>\
		</div>\
		<div class=\"col-4 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/3',document)\">3</button>\
		</div>\
	</div>\
	<div class=\"row\">\
		<div class=\"col-4 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/4',document)\">4</button>\
		</div>\
		<div class=\"col-4 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/5',document)\">5</button>\
		</div>\
		<div class=\"col-4 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/6',document)\">6</button>\
		</div>\
	</div>\
	<div class=\"row\">\
		<div class=\"col-4 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/7',document)\">7</button>\
		</div>\
		<div class=\"col-4 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/8',document)\">8</button>\
		</div>\
		<div class=\"col-4 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/9',document)\">9</button>\
		</div>\
	</div>\
	<br/>\
	<div class=\"row\">\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/txt',document)\">Televideo</button>			 \
		</div>\
		<div class=\"col-1 align-items-center\"></div>\
		<div class=\"col-4 align-items-center\">\
			 <button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/0',document)\">0</button>\
		</div>\
		<div class=\"col-1 align-items-center\"></div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/sub',document)\">Subtitles</button>\
		</div>\
	</div>\
	\
	<br/><br/>\
	\
	<div class=\"row\">\
		<div class=\"col-1 align-items-center\"></div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/volup',document)\"><span class=\"glyphicon glyphicon-volume-up white\"></button>			 \
		</div>\
		<div class=\"col-4 align-items-center\"></div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/chup',document)\"><span class=\"glyphicon glyphicon-plus white\"></button>\
		</div>\
		<div class=\"col-1 align-items-center\"></div>\
	</div>\
	<div class=\"row\">\
		<div class=\"col-1 align-items-center\"></div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/voldown',document)\"><span class=\"glyphicon glyphicon-volume-down white\"></button>		 \
		</div>\
		<div class=\"col-1 align-items-center\"></div>\
		<div class=\"col-2 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/mute',document)\"><span class=\"glyphicon glyphicon-volume-off white\"></button>		 \
		</div>\
		<div class=\"col-1 align-items-center\"></div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/chdown',document)\"><span class=\"glyphicon glyphicon-minus white\"></button>\
		</div>\
		<div class=\"col-1 align-items-center\"></div>\
	</div>\
	\
	<br/><br/>\
\
	<div class=\"row\">\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/guide',document)\">Guide</button>\
		</div>\
		<div class=\"col-2 align-items-center\"></div>\
		<div class=\"col-2 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/up',document)\"><span class=\"glyphicon glyphicon-chevron-up white\"></button>\
		</div>\
		<div class=\"col-2 align-items-center\"></div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/info',document)\"><span class=\"glyphicon glyphicon-info-sign white\"></button>\
		</div>\
	</div>\
	<br/>\
	<div class=\"row\">\
		<div class=\"col-1 align-items-center\"></div>\
		<div class=\"col-2 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/left',document)\"><span class=\"glyphicon glyphicon-chevron-left white\"></span></button>\
		</div>\
		<div class=\"col-1 align-items-center\"></div>\
		<div class=\"col-4 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/enter',document)\">Enter</button>\
		</div>\
		<div class=\"col-1 align-items-center\"></div>\
		<div class=\"col-2 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/right',document)\"><span class=\"glyphicon glyphicon-chevron-right white\"></button>\
		</div>\
		<div class=\"col-1 align-items-center\"></div>\
	</div>\
	<br/>\
	<div class=\"row\">\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/return',document)\">Return</button>\
		</div>\
		<div class=\"col-2 align-items-center\"></div>\
		<div class=\"col-2 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/down',document)\"><span class=\"glyphicon glyphicon-chevron-down white\"></button>\
		</div>\
		<div class=\"col-2 align-items-center\"></div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/options',document)\">Options</button>\
		</div>\
	</div>\
	<br/>\
	<div class=\"row\">\
		<div class=\"col-3 align-items-center\"></div>\
		<div class=\"col-6 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/home',document)\">HOME</button>\
		</div>\
		<div class=\"col-3 align-items-center\"></div>\
	</div>\
	<br/>\
	<div class=\"row\">\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/prev',document)\">Prev</button>\
		</div>\
		<div class=\"col-6 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/play',document)\">PLAY</button>\
		</div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/next',document)\">Next</button>\
		</div>\
	</div>\
	<div class=\"row\">\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/titlelist',document)\">Title List</button>\
		</div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/rec',document)\">Rec</button>\
		</div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/pause',document)\">Pause</button>\
		</div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton black text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/stop',document)\">Stop</button>\
		</div>\
	</div>\
	<br/>\
	<div class=\"row\">\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton red text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/red',document)\">&nbsp;</button>\
		</div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton green2 text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/green',document)\">&nbsp;</button>\
		</div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton yellow text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/yellow',document)\">&nbsp;</button>\
		</div>\
		<div class=\"col-3 align-items-center\">\
			<button class=\"myButton blue text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('remotes/blue',document)\">&nbsp;</button>\
		</div>\
	</div>\
\
	<br/><br/>\
	\
	<div class=\"row\">\
		<div class=\"col-4 align-items-center\"></div>\
		<div class=\"col-4 align-items-center\"></div>\
		<div class=\"col-4 align-items-center\">\
			<button class=\"myButton green text-center align-items-center align-self-center btn btn-block btn-lg\" onclick=\"do('restart',document)\">Restart system</button>\
		</div>\
	</div>\
</div>\
\
<br/><br/><br/><br/>\
\
<div class=\"col-8\">\
    <form class=\"\" action=\"settings\" method=\"post\">\
        <div class=\"form-group\"> <label>WiFi SSID</label>\
			<input name=\"ssid\" type=\"text\" class=\"form-control\" placeholder=\"Enter new WiFi SSID\">\
		</div>\
        <div class=\"form-group\"> <label>WiFi Password</label>\
			<input name=\"pwd\" type=\"password\" class=\"form-control\" placeholder=\"Enter WiFi Password\">\
		</div>\
        <button type=\"submit\" class=\"btn btn-primary\">Save config</button>\
    </form>\
</div>\
</body>\
</html>";
