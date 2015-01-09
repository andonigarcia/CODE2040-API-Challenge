#CODE2040-API-Challenge Web Page

This is my repository to show the source code for my web interface to the [CODE2040 API Challenge](http://challenge.code2040.org).

Everything functionally should work out. It is made mobile-friendly, but looks a little "brute" because I avoided using any frameworks (like Bourbon or Bootstrap) or external libraries (like JQueryUI) for the design. (Although admittedly I did use JQuery for the functionality to show my ability to use JQuery.ajax() and Google Fonts, because I just couldn't stand using Impact, Times, and serif for the whole thing...sorry you've gotta have a minimum design appreciation even if you stray from the 'out-of-the-box' frameoworks).

Also, I found a bug* in the CODE2040 server such that it does not check email or url responses. As such, you can type any email or url into the input and recieve a unique token back (I'm assuming it's from the hash of the email/url such that its unique, but it very well may be the case that the tokens aren't very unique either).

*It might not be a bug and might have been intentional for all I know. But I do know that the server does not check the url or email for if they are actually registered. I sanitize my inputs client-side (thanks to the ease of HTML5 and JSON) so you can't put raw code, but still you can put any email or url and the server will accept it.
