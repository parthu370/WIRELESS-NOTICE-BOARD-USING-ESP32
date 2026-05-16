#include "server_routes.h"
#include "storage.h"

void setupServer() {

  // ===== LOGIN PAGE =====

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {

    request->send(200, "text/html",

      "<h2>Login</h2>"
      "User <input id=u><br><br>"
      "Pass <input id=p type=password><br><br>"
      "<button onclick='login()'>Login</button>"

      "<script>"

      "function login(){"

      "fetch('/login?u='+u.value+'&p='+p.value)"

      ".then(r=>r.text())"

      ".then(t=>{"

      "if(t=='ok') location='/panel';"

      "else alert('Wrong login');"

      "});}"

      "</script>"
    );
  });

  // ===== LOGIN CHECK =====

  server.on("/login", HTTP_GET, [](AsyncWebServerRequest *request) {

    String u = request->getParam("u")->value();

    String p = request->getParam("p")->value();

    if (u == "admin" && p == "1234") {

      loggedIn = true;

      request->send(200, "text/plain", "ok");

    } else {

      request->send(200, "text/plain", "fail");
    }
  });

  // ===== SET EXPIRY =====

  server.on("/setExpiry", HTTP_GET,
    [](AsyncWebServerRequest *request){

    if (request->hasParam("d")) {

      lastExpiry = request->getParam("d")->value();
    }

    request->send(200, "text/plain", "ok");
  });

  // ===== DELAY =====

  server.on("/delay", HTTP_GET,
    [](AsyncWebServerRequest *request){

    if(request->hasParam("d")) {

      slideDelay = request->getParam("d")->value().toInt();

      if (slideDelay < 1) {
        slideDelay = 1;
      }
    }

    request->send(200, "text/plain", "ok");
  });

  // ===== PANEL =====

  server.on("/panel", HTTP_GET,
    [](AsyncWebServerRequest *request) {

    if (!loggedIn) {

      request->redirect("/");

      return;
    }

    request->send(200, "text/html", R"rawliteral(

<h2>ESP32 Notice Board</h2>

<input type=file id=file><br><br>

Expiry Date:
<input type="date" id="date"><br><br>

<button onclick=upload()>Upload</button><br><br>

Delay:
<input id="delay" value="4">

<button onclick="setDelay()">Set Delay</button>

<h3>Images</h3>

<div id=list></div>

<script>

let f;

file.onchange = e => f = e.target.files[0];

function upload(){

  let d = document.getElementById("date").value;

  fetch("/setExpiry?d=" + d).then(()=>{

    let data = new FormData();

    data.append("image", f);

    fetch("/upload", {

      method: "POST",

      body: data

    }).then(()=>location.reload());
  });
}

function setDelay(){

  let d = document.getElementById("delay").value;

  fetch("/delay?d=" + d);
}

function load(){

  fetch("/list")

  .then(r=>r.json())

  .then(d=>{

    let html="";

    d.forEach(i=>{

      html += `
      <img src="/img?name=${i.name}" width=120><br>
      <b>${i.name}</b><br>
      Expiry: ${i.exp}<br>
      <button onclick="del('${i.name}')">
      Delete
      </button><hr>`;
    });

    list.innerHTML = html;
  });
}

function del(n){

  fetch("/delete?name="+n)

  .then(()=>location.reload());
}

load();

</script>

)rawliteral");
  });

  // ===== IMAGE =====

  server.on("/img", HTTP_GET,
    [](AsyncWebServerRequest *request) {

    String name = request->getParam("name")->value();

    request->send(LittleFS, "/" + name, "image/jpeg");
  });

  // ===== LIST =====

  server.on("/list", HTTP_GET,
    [](AsyncWebServerRequest *request) {

    String json = "[";

    for (int i = 0; i < imageCount; i++) {

      String exp = "No expiry";

      String meta = "/" + images[i] + ".txt";

      if (LittleFS.exists(meta)) {

        File f = LittleFS.open(meta, "r");

        uint32_t t = f.readString().toInt();

        f.close();

        DateTime dt(t);

        exp = String(dt.day()) + "/" +
              String(dt.month()) + "/" +
              String(dt.year());
      }

      json += "{\"name\":\"" +
              images[i] +
              "\",\"exp\":\"" +
              exp +
              "\"}";

      if (i < imageCount - 1) {
        json += ",";
      }
    }

    json += "]";

    request->send(200, "application/json", json);
  });

  // ===== DELETE =====

  server.on("/delete", HTTP_GET,
    [](AsyncWebServerRequest *request) {

    deleteImage(request->getParam("name")->value());

    loadImages();

    currentImage = 0;

    request->send(200, "text/plain", "ok");
  });

  // ===== UPLOAD =====

  server.on("/upload", HTTP_POST,

    [](AsyncWebServerRequest *request){

      request->send(200);
    },

    [](AsyncWebServerRequest *request,
       String filename,
       size_t index,
       uint8_t *data,
       size_t len,
       bool final){

      static File file;

      static String fname;

      if(index == 0){

        fname = "/img" + String(millis()) + ".jpg";

        file = LittleFS.open(fname, "w");
      }

      if(len) {
        file.write(data, len);
      }

      if(final){

        file.close();

        if (lastExpiry != "") {

          int y = lastExpiry.substring(0,4).toInt();

          int m = lastExpiry.substring(5,7).toInt();

          int d = lastExpiry.substring(8,10).toInt();

          DateTime future(y,m,d,23,59,59);

          File f = LittleFS.open(fname + ".txt", "w");

          f.print(String(future.unixtime()));

          f.close();
        }

        lastExpiry = "";

        loadImages();

        currentImage = 0;

        lastDrawn = "";
      }
    });

  server.begin();
}
