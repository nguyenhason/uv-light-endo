#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;
ESP8266WebServer server(80);
boolean value;
boolean Status;

const char *ssid = "UV Light Endoscopy";
const char *password = "12345678";

// IPAddress staticIP(172,16,43,200);
// IPAddress gateway(172,16,43,254);
// IPAddress subnet(255,255,252,0);

String webPageStop =
    {
        "<!DOCTYPE html>"
        "<html lang="
        "en"
        ">"
        "<head>"
        "<meta charset="
        "UTF-8"
        "/>"
        "<meta http-equiv="
        "X-UA-Compatible"
        " content="
        "IE=edge"
        " />"
        "<meta name="
        "viewport"
        "content="
        "width=device-width, initial-scale=1.0"
        "/>"
        "<title>City International Hospital</title>"
        "<style>"
        "html"
        "{"
        "font-size: 62.5%;"
        "background: #e6f0ff;"
        "}"
        "body"
        "{"
        "font-size: 2.1rem;"
        "font-family: sans-serif;"
        "text-align: center;"
        "}"

        ".control"
        "{"
        "margin-top: 200px;"
        "justify-content: center;"
        "}"
        "a "
        "{"
        "text-decoration: none;"
        "display: inline-block;"
        "min-width: 300px;"
        "background: #0f1b4c;"
        "border-radius: 12px;"

        "font-weight: 500;"
        "font-size: 4rem;"
        "text-align: center;"
        "padding: 30px 28px;"
        "margin: 50px;"
        "color: #ffffff;"
        "}"

        ".btn-sub:hover"
        "{"
        "opacity: 0.5;"
        "}"
        ".btn"
        "{"
        "margin-top: 10px;"
        "}"
        "h1"
        "{"
        "font-weight: 700;"
        "font-size: 6.4rem;"
        "line-height: 1.19;"
        "color: #000336;"
        "}"
        "p,"
        "h2"
        "{"
        "font-style: normal;"
        "font-weight: 600;"
        "font-size: 5rem;"
        "line-height: 1;"
        "text-align: center;"
        "color: #000339;"
        "}"
        ".footer {"
        "margin-top: 350px;"
        "text-align: center;"
        "}"
        ".copyright {"
        "font-weight: 400;"
        "font-size: 2.5rem;"
        "color: #7B8087;"
        "}"
        ".main-content {"
        "border: #7b8087 solid;"
        "border-radius: 12px;"
        "}"

        " </style>"
        "</head>"
        "<body>"
        "<div class="
        "main-content"
        ">"
        "<div class="
        "control"
        ">"
        "<h1 class="
        "title"
        ">City International Hospital</h1>"
        "<h2 class="
        "title"
        ">UV Light - Endoscopy</h2>"
        "<div class="
        "btn"
        ">"
        "<a href='/Set_timer10' class='btn-sub btn-10'>30 minutes</a>"
        "<a href='/Set_timer15'class='btn-sub btn-15'>60 minutes</a>"
        "<h2>Status : Stopped </h2>"
        "</div>"
        "<a href='/Start' class='btn-sub'>Start</a>"
        "<a href='/Update' class='btn-sub'>Check Status</a>"
        "</div>"
        "<div class="
        "footer"
        ">"
        "<p class="
        "copyright"
        ">Copyright 2023, All rights reserved.</p>"
        "<p class="
        "copyright"
        ">By Biomedical Department</p>"
        "</div>"
        "</div>"
        "</body>"
        "</html>"};

String webPageTimer =
    {
        "<!DOCTYPE html>"
        "<html lang="
        "en"
        ">"
        "<head>"
        "<meta charset="
        "UTF-8"
        "/>"
        "<meta http-equiv="
        "X-UA-Compatible"
        " content="
        "IE=edge"
        " />"
        "<meta name="
        "viewport"
        "content="
        "width=device-width, initial-scale=1.0"
        "/>"
        "<title>City International Hospital</title>"
        "<style>"
        "html"
        "{"
        "font-size: 62.5%;"
        "background: #e6f0ff;"
        "}"
        "body"
        "{"
        "font-size: 2.1rem;"
        "font-family: sans-serif;"
        "text-align: center;"
        "}"

        ".control"
        "{"
        "margin-top: 200px;"
        "justify-content: center;"
        "}"
        "a "
        "{"
        "text-decoration: none;"
        "display: inline-block;"
        "min-width: 300px;"
        "background: #0f1b4c;"
        "border-radius: 12px;"

        "font-weight: 500;"
        "font-size: 4rem;"
        "text-align: center;"
        "padding: 30px 28px;"
        "margin: 50px;"
        "color: #ffffff;"
        "}"
        ".btn-10"
        "{"
        "display: none;"
        "}"
        ".btn-15"
        "{"
        "display: none;"
        "}"
        ".btn-sub:hover"
        "{"
        "opacity: 0.5;"
        "}"
        ".btn"
        "{"
        "margin-top: 10px;"
        "}"
        "h1"
        "{"
        "font-weight: 700;"
        "font-size: 6.4rem;"
        "line-height: 1.19;"
        "color: #000336;"
        "}"
        "p,"
        "h2"
        "{"
        "font-style: normal;"
        "font-weight: 600;"
        "font-size: 5rem;"
        "line-height: 1;"
        "text-align: center;"
        "color: #000339;"
        "}"
        ".footer {"
        "margin-top: 350px;"
        "text-align: center;"
        "}"
        ".copyright {"
        "font-weight: 400;"
        "font-size: 2.5rem;"
        "color: #7B8087;"
        "}"
        " </style>"
        "</head>"
        "<body>"
        "<div class="
        "main-content"
        ">"
        "<div class="
        "control"
        ">"
        "<h1 class="
        "title"
        ">City International Hospital</h1>"
        "<h2 class="
        "title"
        ">UV Light - Endoscopy</h2>"
        "<div class="
        "btn"
        ">"
        "<a href='/Set_timer10' class='btn-sub btn-10'>30 minutes</a>"
        "<a href='/Set_timer15'class='btn-sub btn-15'>60 minutes</a>"
        "<h2>Status : Running...^^ </h2>"
        "</div>"
        "<a href='/Stop' class='btn-sub'>Stop</a>"
        "<a href='/Update' class='btn-sub'>Check Status</a>"
        "</div>"
        "<div class="
        "footer"
        ">"
        "<p class="
        "copyright"
        ">Copyright 2023, All rights reserved.</p>"
        "<p class="
        "copyright"
        ">By Biomedical Department</p>"
        "</div>"
        "</div>"
        "</body>"
        "</html>"};

String webPagePleaseStart30 =
    {
        "<!DOCTYPE html>"
        "<html lang="
        "en"
        ">"
        "<head>"
        "<meta charset="
        "UTF-8"
        "/>"
        "<meta http-equiv="
        "X-UA-Compatible"
        " content="
        "IE=edge"
        " />"
        "<meta name="
        "viewport"
        "content="
        "width=device-width, initial-scale=1.0"
        "/>"
        "<title>City International Hospital</title>"
        "<style>"
        "html"
        "{"
        "font-size: 62.5%;"
        "background: #e6f0ff;"
        "}"
        "body"
        "{"
        "font-size: 2.1rem;"
        "font-family: sans-serif;"
        "text-align: center;"
        "}"

        ".control"
        "{"
        "margin-top: 200px;"
        "justify-content: center;"
        "}"
        "a "
        "{"
        "text-decoration: none;"
        "display: inline-block;"
        "min-width: 300px;"
        "background: #0f1b4c;"
        "border-radius: 12px;"

        "font-weight: 500;"
        "font-size: 4rem;"
        "text-align: center;"
        "padding: 30px 28px;"
        "margin: 50px;"
        "color: #ffffff;"
        "}"
        ".btn-10"
        "{"
        "opacity: 0.2;"
        "}"
        ".btn-15"
        "{"
        "display: none;"
        "}"
        ".btn-sub:hover"
        "{"
        "opacity: 0.5;"
        "}"
        ".btn"
        "{"
        "margin-top: 10px;"
        "}"
        "h1"
        "{"
        "font-weight: 700;"
        "font-size: 6.4rem;"
        "line-height: 1.19;"
        "color: #000336;"
        "}"
        "p,"
        "h2"
        "{"
        "font-style: normal;"
        "font-weight: 600;"
        "font-size: 5rem;"
        "line-height: 1;"
        "text-align: center;"
        "color: #000339;"
        "}"
        ".footer {"
        "margin-top: 350px;"
        "text-align: center;"
        "}"
        ".copyright {"
        "font-weight: 400;"
        "font-size: 2.5rem;"
        "color: #7B8087;"
        "}"
        " </style>"
        "</head>"
        "<body>"
        "<div class="
        "main-content"
        ">"
        "<div class="
        "control"
        ">"
        "<h1 class="
        "title"
        ">City International Hospital</h1>"
        "<h2 class="
        "title"
        ">UV Light - Endoscopy</h2>"
        "<div class="
        "btn"
        ">"
        "<a href='/Set_timer10' class='btn-sub btn-10'>30 minutes</a>"
        "<a href='/Set_timer15' class='btn-sub btn-15'>60 minutes</a>"
        "<h2>Status : Please Start 30 minutes !!! </h2>"
        "</div>"
        "<a href='/Start' class='btn-sub'>Start</a>"
        "<a href='/Stop' class='btn-sub'>Back</a>"
        "</div>"
        "<div class="
        "footer"
        ">"
        "<p class="
        "copyright"
        ">Copyright 2023, All rights reserved.</p>"
        "<p class="
        "copyright"
        ">By Biomedical Department</p>"
        "</div>"
        "</div>"
        "</body>"
        "</html>"};
String webPagePleaseStart60 =
    {
        "<!DOCTYPE html>"
        "<html lang="
        "en"
        ">"
        "<head>"
        "<meta charset="
        "UTF-8"
        "/>"
        "<meta http-equiv="
        "X-UA-Compatible"
        " content="
        "IE=edge"
        " />"
        "<meta name="
        "viewport"
        "content="
        "width=device-width, initial-scale=1.0"
        "/>"
        "<title>City International Hospital</title>"
        "<style>"
        "html"
        "{"
        "font-size: 62.5%;"
        "background: #e6f0ff;"
        "}"
        "body"
        "{"
        "font-size: 2.1rem;"
        "font-family: sans-serif;"
        "text-align: center;"
        "}"

        ".control"
        "{"
        "margin-top: 200px;"
        "justify-content: center;"
        "}"
        "a "
        "{"
        "text-decoration: none;"
        "display: inline-block;"
        "min-width: 300px;"
        "background: #0f1b4c;"
        "border-radius: 12px;"

        "font-weight: 500;"
        "font-size: 4rem;"
        "text-align: center;"
        "padding: 30px 28px;"
        "margin: 50px;"
        "color: #ffffff;"
        "}"
        ".btn-10"
        "{"
        "display: none;"
        "}"
        ".btn-15"
        "{"
        "opacity: 0.2;"
        "}"
        ".btn-sub:hover"
        "{"
        "opacity: 0.5;"
        "}"
        ".btn"
        "{"
        "margin-top: 10px;"
        "}"
        "h1"
        "{"
        "font-weight: 700;"
        "font-size: 6.4rem;"
        "line-height: 1.19;"
        "color: #000336;"
        "}"
        "p,"
        "h2"
        "{"
        "font-style: normal;"
        "font-weight: 600;"
        "font-size: 5rem;"
        "line-height: 1;"
        "text-align: center;"
        "color: #000339;"
        "}"
        ".footer {"
        "margin-top: 350px;"
        "text-align: center;"
        "}"
        ".copyright {"
        "font-weight: 400;"
        "font-size: 2.5rem;"
        "color: #7B8087;"
        "}"
        " </style>"
        "</head>"
        "<body>"
        "<div class="
        "main-content"
        ">"
        "<div class="
        "control"
        ">"
        "<h1 class="
        "title"
        ">City International Hospital</h1>"
        "<h2 class="
        "title"
        ">UV Light - Endoscopy</h2>"
        "<div class="
        "btn"
        ">"
        "<a href='/Set_timer10' class='btn-sub btn-10'>30 minutes</a>"
        "<a href='/Set_timer15' class='btn-sub btn-15'>60 minutes</a>"
        "<h2>Status : Please Start 60 minutes !!! </h2>"
        "</div>"
        "<a href='/Start' class='btn-sub'>Start</a>"
        "<a href='/Stop' class='btn-sub'>Back</a>"
        "</div>"
        "<div class="
        "footer"
        ">"
        "<p class="
        "copyright"
        ">Copyright 2023, All rights reserved.</p>"
        "<p class="
        "copyright"
        ">By Biomedical Department</p>"
        "</div>"
        "</div>"
        "</body>"
        "</html>"};
void Set_timer30()
{
    value = 0;
    server.send(200, "text/html", webPagePleaseStart30);
}
void Set_timer60()
{
    value = 1;
    server.send(200, "text/html", webPagePleaseStart60);
}
void Stop()
{
    value = 2;
    digitalWrite(4, LOW);
    server.send(200, "text/html", webPageStop);
}
void updateStatus()
{
    if (Status == 0)
    {
        server.send(200, "text/html", webPageStop);
    }
    else
    {
        server.send(200, "text/html", webPageTimer);
    }
}

void Start()
{
    delay(10);
    if (value == 0)
    {
        digitalWrite(4, HIGH);
        Status = 1;
        server.send(200, "text/html", webPageTimer);
        for (int i = 0; i <= 1800; i++)
        {
            server.handleClient();
            if (value == 2)
            {
                break;
            }
            delay(1000);
        }
        digitalWrite(4, LOW);
        Status = 0;
    }
    delay(10);
    if (value == 1)
    {
        digitalWrite(4, HIGH);
        Status = 1;
        server.send(200, "text/html", webPageTimer);
        for (int i = 0; i <= 3600; i++)
        {
            server.handleClient();
            if (value == 2)
            {
                break;
            }
            delay(1000);
        }
        digitalWrite(4, LOW);
        Status = 0;
    }
}
void setup()
{
    // pinMode(0, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);

    Serial.begin(115200);
    //  WiFi.config(staticIP, gateway, subnet);
    while (WiFi.softAP(ssid, password) == false)
    {
        Serial.print(".");
        delay(300);
    }
    //  Serial.println();
    //
    //  WiFi.begin(ssid, password);
    // WiFi.config(staticIP, gateway, subnet);
    //  while (WiFi.status() != WL_CONNECTED)
    //  {
    //    delay(500);
    //    Serial.print(".");
    //  }
    //  Serial.println("");
    //  Serial.println("WiFi connected");
    //  Serial.println("IP address: ");
    //  Serial.println(WiFi.localIP());
    //  if (mdns.begin("esp8266", WiFi.localIP()))
    //  Serial.println("MDNS responder started");
    //

    server.on("/", Stop);
    server.on("/Set_timer10", Set_timer30);
    server.on("/Set_timer15", Set_timer60);
    server.on("/Start", Start);
    server.on("/Stop", Stop);
    server.on("/Update", updateStatus);
    server.begin();
}
void loop()
{
    server.handleClient();
}