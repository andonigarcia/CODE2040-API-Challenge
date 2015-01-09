# Web Interface for CODE2040 API Challenge

The code in this repository will produce a robust web-side application for the CODE2040 API Challenge. I have made sure all the functionlity works well even in corner cases. Further, I have made the site mobile-first. I tried to stray away from frameworks like Bootstrap, Bourbon, or JQueryUI and rather show my ability with pure CSS. Despite this, I still caved and used Google Fonts.

## How To Use

1. Go to [the website](http://andonigarcia.github.io/CODE2040-API-Challenge)
2. Either:
  * Enter your credentials (if you are a CODE2040 applicant)
  * Click `Register!` to trigger my credentials
  * Enter false credentials (explained below)
3. Click on the tabs on the left to go through each stage

## Server Side Bug

Upon testing this, I entered false email and github url information to see if I could handle the response. To my surprise, the server spit out a new unique string. I tried several more variants before coming to the realization that the server on the back end does not check their inputs to see if indeed that email is a registered applicant **NOR DO THEY CHECK** if that url even points to github. I emailed them about this vulnerability without a response.

As such, I use HTML5 to sanitize the inputs to only url's and email's and use JQuery.sanitize to hopefully minimize the attack front. That said, I know **for a fact** that this does not prevent malicious code from being sent to the server. I am not sure if this is a bug or intentional from the server-side, but it nonetheless is a big potential attack front. Please do not enter malicious code, as CODE2040 is a good program with good intentions and does not deserve that kind of unethical behavior.
