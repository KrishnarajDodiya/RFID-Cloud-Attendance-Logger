function doGet(e) {
  var uid = e.parameter.uid;
  var name = e.parameter.name;

  if (!uid || !name) {
    return ContentService.createTextOutput("Missing parameters");
  }

  var sheet = SpreadsheetApp.openById("11GKvGr9y3SPhQHGytvPuQFFS7Usc_SpUMTbpyHFJuns").getActiveSheet();

  // Append UID, Name, and Timestamp
  sheet.appendRow([new Date(), uid, name]);

  return ContentService.createTextOutput("Logged: " + uid + ", " + name);
}
