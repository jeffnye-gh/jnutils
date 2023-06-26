# Javascript utilities

Various js utilities I keep around for reference. Presently there are
two CORS implementation examples.

--------------
# Cross origin error work arounds

A browser will issue a cross origin blocked error message when js or html
read data from some external files. For example when charting javascript 
attempts to directly load the chart data from a json file, the 
browser will block the attempt.

There are atleast two solutions. Cross Origin Resource Sharing (CORS) or JSON 
with padding, JSONP. JSONP is simpler to implement. CORS addresses security 
concerns when access to the base html/javascript is made by unknown or
public requests.

If you have the option use CORS. It is more modern and likely more secure.

--------------
## JSONP
When the accesses are strictly internal and known to be trusted, JSONP
provides a simple solution to COR errors. The data is wrapped so that it 
is correct javascript, the wrapped data now appears as an extension to
the script and is appended to the main script.

This is the reference example:

```
jsonp/index.html   the JSONP example index file
jsonp/script.js    javascript using the JSONP idiom
jsonp/data.jsonp   this is JSON data wrapped in a handler callback
jsonp/data.json    the same data without the wrapper, syntax correct JSON
```

The data in data.jsonp is wrapped in handleChartData(). data.jsonp is loaded 
as a script appended to the main script.

--------------
## CORS 

CORS uses a web proxy to validate accesses to local data. The example
files are:

```
cors/index.html   main html
cors/script.js    charting java script
cors/data.json    chart data
cors/server.js    runs a local server on port :3000
```
CORS requires packages to be present. If npm is not already installed
install it using apt, then install the javascript packages using npm.

```
apt install npm nodejs 
npm install nodejs cors express
```
To run the example start a local server and browse to cors/index.html

```
cd cors
node server.js &
<open browser and point to cors/index.html>
```

