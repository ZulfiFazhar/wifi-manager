#include "wifi_manager.h"

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  
  loadWiFiCredentials();  // Load stored SSID and password from EEPROM

  // Prompt user for mode selection
  Serial.println("Select Mode:");
  Serial.println("1: Access Point (AP) Mode");
  Serial.println("2: Station Mode (Connect to existing Wi-Fi)");

  while (mode == 0) {
    if (Serial.available() > 0) {
      char input = Serial.read();
      if (input == '1') {
        mode = 1;
        Serial.println("You selected Access Point (AP) mode.");
      } else if (input == '2') {
        mode = 2;
        Serial.println("You selected Station (Wi-Fi) mode.");
      } else {
        Serial.println("Invalid input. Please enter 1 or 2.");
      }
    }
  }

  if (mode == 1) {
    setupAPMode();
  } else if (mode == 2) {
    setupStationMode();
  }

  server.begin();  // Start the web server
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // Print a message out in the serial port
    String currentLine = "";                // Make a String to hold incoming data from the client
    while (client.connected()) {            // Loop while the client's connected
      if (client.available()) {             // If there's bytes to read from the client,
        char c = client.read();             // Read a byte, then
        Serial.write(c);                    // Print it out the serial monitor
        header += c;
        if (c == '\n') {                    // If the byte is a newline character
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            client.println("<!DOCTYPE html>");
            client.println("<html lang=\"en\">");
            client.println("<head>");
            client.println("<meta charset=\"UTF-8\" />");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />");
            client.println("<title>ESP32 WiFi Manager</title>");
            client.println("<style>");
            client.println("  * { margin: 0; padding: 0; }");
            client.println("  body { background-color: #093731; color: white; font-family: Helvetica; overflow: hidden; }");
            client.println("  .container { display: flex; justify-content: center; align-items: center; flex-direction: column; height: 90vh; }");
            client.println("  .logo-container { display: flex; flex-direction: row; justify-content: center; align-items: center; margin-bottom: 2rem; }");
            client.println("  .logo-identity { display: flex; flex-direction: column; margin-left: 1rem; }");
            client.println("  .logo-identity h1 { font-size: 2rem; font-weight: 700; text-transform: uppercase; letter-spacing: 0.5rem; }");
            client.println("  .logo-identity h2 { font-size: 1rem; }");
            client.println("  .form-container { display: flex; flex-direction: column; width: 300px; margin: auto; }");
            client.println("  .form-group { display: flex; justify-content: space-between; margin-bottom: 10px; }");
            client.println("  label { flex: 1; padding: 0.75rem; }");
            client.println("  input { flex: 2; padding: 0.75rem; border: solid 1px white; background-color: transparent; border-radius: 1rem; color: white; font-weight: 700; cursor: text; }");
            client.println("  .button { margin-top: 10px; padding: 10px; background-color: #4caf50; color: white; border: none; cursor: pointer; width: 100%; }");
            client.println("  .button:hover { background-color: #45a049; }");
            client.println("</style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<div class='container'>");
            client.println("  <div class='logo-container'>");
            client.println("    <svg width='80' height='80' viewBox='0 0 208 235' fill='none' xmlns='http://www.w3.org/2000/svg'>");
            client.println("      <mask id='mask0_717_135' style='mask-type: alpha' maskUnits='userSpaceOnUse' x='0' y='0' width='208' height='235'>");
            client.println("        <path fill-rule='evenodd' clip-rule='evenodd' d='M16.5118 117.691C46.2146 26.5569 86.7941 1.29964 103.552 0.0122833V0L103.636 0.00595012L103.721 0V0.0122833C120.479 1.29964 161.058 26.5569 190.761 117.691C220.565 209.134 200.921 233.688 200.921 233.688C200.921 233.688 174.335 240.123 152.66 211.674C144.741 201.281 137.034 194.413 130.082 190.007C158.962 171.845 141.722 125.845 106.721 73.7282C56.8695 138.706 52.6626 175.054 77.1717 190.019C70.225 194.426 62.5243 201.29 54.6131 211.674C32.9377 240.123 6.35142 233.688 6.35142 233.688C6.35142 233.688 -13.2919 209.134 16.5118 117.691ZM89.5294 184.271C95.56 182.509 100.375 182.698 103.346 183.61C98.6315 173.982 99.4424 161.913 100.751 142.431C100.787 141.895 100.824 141.353 100.86 140.806C90.8128 160.128 89.308 171.746 89.5294 184.271Z' fill='#99D000' />");
            client.println("      </mask>");
            client.println("      <g mask='url(#mask0_717_135)'>");
            client.println("        <g filter='url(#filter0_i_717_135)'>");
            client.println("          <path fill-rule='evenodd' clip-rule='evenodd' d='M16.5118 117.691C46.2146 26.5569 86.7941 1.29964 103.552 0.0122833V0L103.636 0.00595012L103.721 0V0.0122833C120.479 1.29964 161.058 26.5569 190.761 117.691C220.565 209.134 200.921 233.688 200.921 233.688C200.921 233.688 174.335 240.123 152.66 211.674C144.741 201.281 137.034 194.413 130.082 190.007C158.962 171.845 141.722 125.845 106.721 73.7282C56.8695 138.706 52.6626 175.054 77.1717 190.019C70.225 194.426 62.5243 201.29 54.6131 211.674C32.9377 240.123 6.35142 233.688 6.35142 233.688C6.35142 233.688 -13.2919 209.134 16.5118 117.691ZM89.5294 184.271C95.56 182.509 100.375 182.698 103.346 183.61C98.6315 173.982 99.4424 161.913 100.751 142.431C100.787 141.895 100.824 141.353 100.86 140.806C90.8128 160.128 89.308 171.746 89.5294 184.271Z' fill='#99D000' />");
            client.println("        </g>");
            client.println("      </g>");
            client.println("      <defs>");
            client.println("        <filter id='filter0_i_717_135' x='0' y='0' width='207.273' height='239.868' filterUnits='userSpaceOnUse' color-interpolation-filters='sRGB'>");
            client.println("          <feFlood flood-opacity='0' result='BackgroundImageFix' />");
            client.println("          <feBlend mode='normal' in='SourceGraphic' in2='BackgroundImageFix' result='shape' />");
            client.println("          <feColorMatrix in='SourceAlpha' type='matrix' values='0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0' result='hardAlpha' />");
            client.println("          <feOffset dy='5.55575' />");
            client.println("          <feGaussianBlur stdDeviation='10.417' />");
            client.println("          <feComposite in2='hardAlpha' operator='arithmetic' k2='-1' k3='1' />");
            client.println("          <feColorMatrix type='matrix' values='0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.25 0' />");
            client.println("          <feBlend mode='normal' in2='shape' result='effect1_innerShadow_717_135' />");
            client.println("        </filter>");
            client.println("      </defs>");
            client.println("    </svg>");
            client.println("    <div class='logo-identity'>");
            client.println("      <h1>Agrimate</h1>");
            client.println("      <h2>WiFi Manager</h2>");
            client.println("    </div>");
            client.println("  </div>");
            client.println("  <form action='setwifi' method='GET'>");
            client.println("    <div class='form-container'>");
            client.println("      <div class='form-group'>");
            client.println("        <label for='username'>Username</label>");
            client.println("        <input type='text' name='username' id='username' value='appusername' />");
            client.println("      </div>");
            client.println("      <div class='form-group'>");
            client.println("        <label for='ssid'>SSID</label>");
            client.println("        <input type='text' name='ssid' id='ssid' value=\"" + wifi_ssid +"\" />");
            client.println("      </div>");
            client.println("      <div class='form-group'>");
            client.println("        <label for='password'>Password</label>");
            client.println("        <input type='text' name='password' id='password' value=\"" + wifi_password +"\" />");
            client.println("      </div>");
            client.println("      <input type='submit' value='Set WiFi' class='button' />");
            client.println("    </div>");
            client.println("  </form>");
            client.println("</div>");
            client.println("</body>");
            client.println("</html>");
            
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    if (header.indexOf("GET /setwifi") >= 0) {
      int ssidIndex = header.indexOf("ssid=");
      int passIndex = header.indexOf("&password=");
      if (ssidIndex != -1 && passIndex != -1) {
        String new_ssid = header.substring(ssidIndex + 5, passIndex);
        String new_password = header.substring(passIndex + 10, header.indexOf(" ", passIndex));

        new_ssid.replace("%20", " ");
        new_password.replace("%20", " ");

        wifi_ssid = new_ssid;
        wifi_password = new_password;

        saveWiFiCredentials(wifi_ssid, wifi_password);
        
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();
        client.println("<!DOCTYPE html><html><body><h1>Wi-Fi settings saved. Reconnecting...</h1></body></html>");
        delay(2000);
        ESP.restart();
      }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
