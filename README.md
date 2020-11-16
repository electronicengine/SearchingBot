# SearchingBot

Hello everyone, In these days which the unit price of data is higher than oil, everyone's problem is finding data and categorize it. We can find all kinds of data on the internet, and thanks to google, it is now easy to access any data. But, The data in the internet is available as a stack and complex manner. I developed the this SearchingBot App to find the desired data in specific web page or file. We can make a search in specific Web-File URL or URL List which got from previous searches. Therefore, You can create a specific search batch.

I have written the app in Qt-C++ and a little bit Qml. You can compile it for Windows, Linux, Mac, Android and also ios. I have tested on Android and Linux.

# App Usage

**The search prefix** 
is the descriptor of the desired data.  It can be html tag, link or any of descriptor of data. The three types of prefix;
  - **Invalid Prefix: * :** this prefix is used for the complete unknown part of the prefix. For example,  you can type app* rather then apple, applet, appreciated... etc.  SearchBot completes the prefix according to search.
  - **Valid Prefix: #:** this prefix is used for extract the desired data from prefix. It is like a variable. You can define multiple of that. Therefore every valid prefix has a variable number. For example #1, #2, #3 ... #9.  You can define at most 9 times of valid prefix in the one search.
  - **Offset Prefix { } :** this prefixes are used for giving offset to the searched page. In some cases, You may want to take only some part of page for searching. For this purpose, you can use this open and close offset prefix.

Example Search:
For example, If I want to get the "Desired Data" section from this content;

> garbage text-start offsettext sometexthere <a href="somelink-dir">Desired Data</a> sometexthere close offsettext-garbage text

I can make a search with this prefix;

>start offsettext{<a href="somelink*>#1</a>}close offsettext

Searching bot extracts the sections place where is "#1" from all of content, and list them in file. If you don't need to offset prefix, don't use it.

As a result;

>**Content:**  sometexthere <a href="somelink-dir">Desired Data</a> sometexthere
>**Search Prefix:** <a href*>#1</a>
>**Search Result:** Desired Data

You can also enter multiple prefix and extract multiple data set by using valid prefix. For Example, You can extract "Desired Data", and the link section from above content with this search prefix;

><a href*>#1</a>, <a href=#2>#1</a>

Notes; You can not use valid and invalid prefix without any latter between them.

As a Result;

>**Content:** sometexthere <a href="somelink-dir">Desired Data</a> sometexthere
>**Search Prefix:** <a href*>#1</a>, <a ref=#2>#1</a>
>**Result:** Desired Data || somelink-dir

**Ban Prefix:**
Ban prefix is used for removing undesired data from extracted data.  For example, Consider that example

>**Content:** sometexthere <a href="somelink-dir"><span> undesired data </span>Desired Data</a> sometexthere 
>**Search Prefix:** <a href=*>#1</a>
>**Ban Prefix:** <span>*</span>
>**Result:** Desired Data

You can use multiple ban prefix by putting "," between them and also invalid prefix "*" in it.

**Split Prefix:**
Split prefix is used for splitting the desired data by one specified char

>**Content:** sometexthere <a href="somelink-dir"><span> undesired data </span>Desired-Data</a> sometexthere
>**Search Prefix:** <a href=*>#1</a> 
>**Ban Prefix:** <span>*</span> 
>**Split Prefix:** -
>**Result:** Desired || Data


**File Operations:**
You can save and load a text file to app by using file buttons in the App. Files can be used for adding multiple search prefixes, ban prefixes and also URL's

For example, If you have a file like that;

>search url1 || ban prefix1 || search Prefix1
>search url2 || ban prefix2 || search prefix2
>search url3 || ban prefix3 || search prefix3
>search url4 || ban prefix4 || search prefix4
>....        || ....        || ...

You can use it for sequential adding by using [1], [2], [3].... [9] keywords.The numbers are indicating the column number. For Example,

>**Search Url :** [1]
>**Ban Prefix :** [2]
>**Search Prefix :** [3]


with this entry, App understands that will put first column to "Search Url", second "Ban Prefix" and third "Search Prefix"

Result:

>**Search Queue 1;**

>**Search Url :** search url1 
>**Ban Prefix :** ban prefix1 
>**Search Prefix :** search Prefix1

>**Search Queue 2;**

>**Search Url :** search url2 
>**Ban Prefix :** ban prefix2
>**Search Prefix :** search Prefix2

>**Search Queue 3;**

>**Search Url :** search url3 
>**Ban Prefix :** ban prefix3 
>**Search Prefix :** search Prefix3

>**Search Queue 4;**

>**Search Url :** search url4 
>**Ban Prefix :** ban prefix4 
>**Search Prefix :** search Prefix4

Also you can use that column keywords with other keywords like that;

>**Search Url :** Begining[1]
>**Ban Prefix :** Someban, key[2]
>**Search Prefix :** someprefix[3]






**file:// Descriptor:** You can make a search in a file rather than web page. the file descriptor is used for specifying the name of the file which is saved by previous searching.

Example usage:

>**Search Url:** file://<file-name>


The application local directory is /home/user/.local/share/SearchingBot in Linux

**file://external/ Descriptor:** If you want to make search in external file, you can specify that file directory with external keyword.

Example usage:

>**Search Url:** file://external/<file-path>/<file-name>



### Tech

Dillinger uses a number of open source projects to work properly:

* [AngularJS] - HTML enhanced for web apps!
* [Ace Editor] - awesome web-based text editor
* [markdown-it] - Markdown parser done right. Fast and easy to extend.
* [Twitter Bootstrap] - great UI boilerplate for modern web apps
* [node.js] - evented I/O for the backend
* [Express] - fast node.js network app framework [@tjholowaychuk]
* [Gulp] - the streaming build system
* [Breakdance](https://breakdance.github.io/breakdance/) - HTML to Markdown converter
* [jQuery] - duh

And of course Dillinger itself is open source with a [public repository][dill]
 on GitHub.

### Installation

Dillinger requires [Node.js](https://nodejs.org/) v4+ to run.

Install the dependencies and devDependencies and start the server.

```sh
$ cd dillinger
$ npm install -d
$ node app
```

For production environments...

```sh
$ npm install --production
$ NODE_ENV=production node app
```

### Plugins

Dillinger is currently extended with the following plugins. Instructions on how to use them in your own application are linked below.

| Plugin | README |
| ------ | ------ |
| Dropbox | [plugins/dropbox/README.md][PlDb] |
| GitHub | [plugins/github/README.md][PlGh] |
| Google Drive | [plugins/googledrive/README.md][PlGd] |
| OneDrive | [plugins/onedrive/README.md][PlOd] |
| Medium | [plugins/medium/README.md][PlMe] |
| Google Analytics | [plugins/googleanalytics/README.md][PlGa] |


### Development

Want to contribute? Great!

Dillinger uses Gulp + Webpack for fast developing.
Make a change in your file and instantaneously see your updates!

Open your favorite Terminal and run these commands.

First Tab:
```sh
$ node app
```

Second Tab:
```sh
$ gulp watch
```

(optional) Third:
```sh
$ karma test
```
#### Building for source
For production release:
```sh
$ gulp build --prod
```
Generating pre-built zip archives for distribution:
```sh
$ gulp build dist --prod
```
### Docker
Dillinger is very easy to install and deploy in a Docker container.

By default, the Docker will expose port 8080, so change this within the Dockerfile if necessary. When ready, simply use the Dockerfile to build the image.

```sh
cd dillinger
docker build -t joemccann/dillinger:${package.json.version} .
```
This will create the dillinger image and pull in the necessary dependencies. Be sure to swap out `${package.json.version}` with the actual version of Dillinger.

Once done, run the Docker image and map the port to whatever you wish on your host. In this example, we simply map port 8000 of the host to port 8080 of the Docker (or whatever port was exposed in the Dockerfile):

```sh
docker run -d -p 8000:8080 --restart="always" <youruser>/dillinger:${package.json.version}
```

Verify the deployment by navigating to your server address in your preferred browser.

```sh
127.0.0.1:8000
```

#### Kubernetes + Google Cloud

See [KUBERNETES.md](https://github.com/joemccann/dillinger/blob/master/KUBERNETES.md)


### Todos

 - Write MORE Tests
 - Add Night Mode

License
----

MIT


**Free Software, Hell Yeah!**

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


   [dill]: <https://github.com/joemccann/dillinger>
   [git-repo-url]: <https://github.com/joemccann/dillinger.git>
   [john gruber]: <http://daringfireball.net>
   [df1]: <http://daringfireball.net/projects/markdown/>
   [markdown-it]: <https://github.com/markdown-it/markdown-it>
   [Ace Editor]: <http://ace.ajax.org>
   [node.js]: <http://nodejs.org>
   [Twitter Bootstrap]: <http://twitter.github.com/bootstrap/>
   [jQuery]: <http://jquery.com>
   [@tjholowaychuk]: <http://twitter.com/tjholowaychuk>
   [express]: <http://expressjs.com>
   [AngularJS]: <http://angularjs.org>
   [Gulp]: <http://gulpjs.com>

   [PlDb]: <https://github.com/joemccann/dillinger/tree/master/plugins/dropbox/README.md>
   [PlGh]: <https://github.com/joemccann/dillinger/tree/master/plugins/github/README.md>
   [PlGd]: <https://github.com/joemccann/dillinger/tree/master/plugins/googledrive/README.md>
   [PlOd]: <https://github.com/joemccann/dillinger/tree/master/plugins/onedrive/README.md>
   [PlMe]: <https://github.com/joemccann/dillinger/tree/master/plugins/medium/README.md>
   [PlGa]: <https://github.com/RahulHP/dillinger/blob/master/plugins/googleanalytics/README.md>
