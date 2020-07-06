function login(){
  var username = document.getElementById("username").value;
  var password = document.getElementById("password").value;
  if ( localStorage.getItem(username) == password){
    alert ("Login successfully");
    return false;
  }
  else{
    alert("Wrong username or password");
    return false;
  }
}

function logon(){
  var username = document.getElementById("username").value;
  var password = document.getElementById("password").value;
  if (password.length < 5) {
    alert("Password should contain at least 5 characters")
    return false;
  }
  var result = /[\\@#.;,:'\\s]/i.exec( password );
  if (result) {
    alert("Wrong characters in password")
    return false;
  }
  localStorage.setItem(username, password)
  alert ("Logon successfully");
  return false;
}
