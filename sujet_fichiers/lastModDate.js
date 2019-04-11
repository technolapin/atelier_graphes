// (C) Denis BUREAU 15/05/2002, mod 17/01/2006
function initArray()
 { // Thanks JavaScript Mailing List for this function
 this.length = initArray.arguments.length
 for (var i = 0; i < this.length; i++)
  this[i+1] = initArray.arguments[i]
 }
function writeLMDate()
 {
 writeLMDateOf( document );
 }
function writeLMDateOf( theMod )
 {
 var DOWArray = new initArray("dimanche","lundi","mardi","mercredi",
                              "jeudi","vendredi","samedi");
 var MOYArray = new initArray("janvier","f&eacute;vrier","mars","avril",
                              "mai","juin","juillet","ao&ucirc;t","septembre",
                              "octobre","novembre","d&eacute;cembre");
 var LastModDate = new Date( theMod.lastModified );
 if ( isNaN( LastModDate ) )
  {
  lmDate = new String( theMod.lastModified );
  document.write( lmDate.substring( 0, lmDate.lastIndexOf(":") ) );
  }
 else
  {
  var dom  = LastModDate.getDate();
  var year = LastModDate.getYear();
  if (year<2000) year = year%100 + 2000;
  document.write(DOWArray[(LastModDate.getDay()+1)]," ");
  document.write((dom==1 ? "1<sup>er</sup>" : dom)," ");
  document.write(MOYArray[(LastModDate.getMonth()+1)]," ");
  document.write(year," &agrave; ");
  document.write(LastModDate.getHours(),"h");
  if (LastModDate.getMinutes() < 10) document.write("0");
  document.write(LastModDate.getMinutes());
  }
 }
