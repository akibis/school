
<script>
var object_names = new Array("readme.txt","system","javavm");
var user_names = new Array("Bob","Lisa","Pete");
object_names.length = 3;
user_names.length = 3;
object_list = new Array();
rights = new Array("r","w","x","l","d");
rights.length = 5;
rights_names = new Array("read","write","execute","list","delete");
rights_names.length = 5;

for(i=0; i<object_names.length; i++) {
  var acl = new Array(user_names.length);

  for(j=0; j<user_names.length; j++) {
    acl[user_names[j]] = new String();
  }

  object_list[object_names[i]] = acl;
}

function user_selectbox(name,extra)
{
  document.write('<select name="' + name + '" ' + extra + '>');
  for(i=0; i<user_names.length; i++) {
    document.write('<option value="' + user_names[i] + '">' + user_names[i]);
  }
  document.write('</select>');
}

function object_selectbox(name)
{
  document.write('<select name="' + name + '">');
  for(i=0; i<object_names.length; i++) {
    document.write('<option value="' + object_names[i] + '">' + object_names[i]);
  }
  document.write('</select>');
}

function rights_checkboxes(prefix, objname)
{
  var i;

  for(i=0; i<rights.length; i++) {
    document.write('         ');
    document.write('<td><input type=checkbox name="' + prefix + rights[i] + '" ');
    document.write("onclick=\"update(this.checked,'" + rights[i] + objname + "');\">");
    document.write("</td>\n");
  }
}

function update_checkboxes()
{
  var ubox = document.mainform.user1;

  uname = ubox.options[ubox.selectedIndex].value;
  for(i=1; i<=3; i++) {
    prefix = "e" + i;
    for(j=0; j<rights.length; j++) {
      fieldname = prefix + rights[j];
      if(test_right(object_names[i-1],uname,rights[j]))
        eval("document.mainform." + fieldname + ".checked = true;");
      else
        eval("document.mainform." + fieldname + ".checked = false;");
    }
  }
}

function test_right(obj, username, right)
{
  if(object_list[obj][username].indexOf(right) == -1)
    return(0);
  else
    return(1);
}

function add_right(obj, username, right)
{
  var i;

//  alert("Before adding " + right + ": " + object_list[obj][username]);
  if(test_right(obj,username, right))
    return(1);
  else
    object_list[obj][username] = "" + object_list[obj][username] + right;
  return(0);
//  alert("After adding " + right + ": " + object_list[obj][username]);
}

function remove_right(obj, username, right)
{
  var newstr;
  var i;

//  alert("Before removing " + right + ": " + object_list[obj][username]);
  newstr = "";
  for(i=0; i<object_list[obj][username].length; i++) {
    if(object_list[obj][username].charAt(i) != right)
      newstr = "" + newstr + object_list[obj][username].charAt(i);
  }  
  object_list[obj][username] = newstr;
//  alert("After removing " + right + ": " + object_list[obj][username]);
}

function test()
{
  add_right("system","Bob","r");
  add_right("system","Bob","w");  
  add_right("readme.txt","Bob","x");
  remove_right("system","Bob","w");
  alert(test_right("system","Bob","w"));
  add_right("readme.txt","Lisa","w");
  alert(test_right("readme.txt","Lisa","w"));
}

function tryaccess()
{
  var uname, oname, right;
  var ubox = document.mainform.user2;
  var obox = document.mainform.obj;

  uname = ubox.options[ubox.selectedIndex].value;
  oname = obox.options[obox.selectedIndex].value;
  for(i=0; i<document.mainform.access.length; i++)
    if(document.mainform.access[i].checked)
      right = rights[i];

  if(test_right(oname,uname,right)) {
    document.mainform.result.value = 'Allowed';
  } else {
    document.mainform.result.value = 'Denied';
  }
}

function update(checked,robject)
{
  var uname, oname, right;
  var str;
  var sbox = document.mainform.user1;

  right = robject.substr(0,1);
  oname = robject.substr(1,robject.length-1);
  uname = sbox.options[sbox.selectedIndex].value;

  if(checked) {
    add_right(oname, uname, right);
  } else {
    remove_right(oname, uname, right);
  }
}

function helpwin()
{
  newwin = window.open('aclhelp.html','ACLHelp','width=300, height=200, scrollbars=yes, resizable=yes');
}
</script>