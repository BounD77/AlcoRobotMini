byte counter_tries = 0;

void WIFIinit() {
    // --------------------Получаем ssid со страницы
    HTTP.on("/ssid", HTTP_GET, []() {
        jsonWrite(configSetup, "ssid", HTTP.arg("ssid"));
        jsonWrite(configSetup, "password", HTTP.arg("password"));
        saveConfig();                 // Функция сохранения данных во Flash
        HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
    });
    // --------------------Получаем ssidap со страницы
    HTTP.on("/ssidap", HTTP_GET, []() {
        jsonWrite(configSetup, "ssidAP", HTTP.arg("ssidAP"));
        jsonWrite(configSetup, "passwordAP", HTTP.arg("passwordAP"));
        saveConfig();                 // Функция сохранения данных во Flash
        HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
    });


    // Попытка подключения к точке доступа
    WiFi.mode(WIFI_STA);
    byte tries = 11;
    String _ssid = jsonRead(configSetup, "ssid");
    String _password = jsonRead(configSetup, "password");
    if (_ssid == "" && _password == "") {
        WiFi.begin();
    }
    else {
        WiFi.begin(_ssid.c_str(), _password.c_str());
    }
    // Делаем проверку подключения до тех пор пока счетчик tries
    // не станет равен нулю или не получим подключение
    while (--tries && WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        tm.setLED(counter_tries, 2);
        counter_tries++;
        delay(1000);


    }
    if (WiFi.status() != WL_CONNECTED)
    {
        // Если не удалось подключиться запускаем в режиме AP
        Serial.println("");
        Serial.println("WiFi up AP");
        RunningLeds(true);//включаем красные леды
        StartAPMode();
    }
    else {
        RunningLeds(false);//включаем зеленые леды
        // Иначе удалось подключиться отправляем сообщение
        // о подключении и выводим адрес IP
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.print("External IP address: ");
        String external_ip = "192.168.0.120";
        Serial.println(external_ip);
        Serial.print("Internal IP address: ");
        String internal_ip = WiFi.localIP().toString();
        Serial.println(internal_ip);
        //если доступ будет только изнутри сети то пишем внутренний адрес в конфигуру
        jsonWrite(configLiveJson, "ip", internal_ip);
        //если извне то пишем внешний
        jsonWrite(configLiveJson, "ip", external_ip);

    }
}

bool StartAPMode() {
    IPAddress apIP(192, 168, 1, 2);
    IPAddress staticGateway(192, 168, 1, 1);
    IPAddress staticSubnet(255, 255, 255, 0);
    jsonWrite(configLiveJson, "ip", apIP.toString());
    // Отключаем WIFI
    WiFi.disconnect();
    // Меняем режим на режим точки доступа
    WiFi.mode(WIFI_AP);
    // Задаем настройки сети
    WiFi.softAPConfig(apIP, staticGateway, staticSubnet);
    //Включаем DNS
    dnsServer.start(53, "*", apIP);
    // Включаем WIFI в режиме точки доступа с именем и паролем
    // хронящихся в переменных _ssidAP _passwordAP
    String _ssidAP = jsonRead(configSetup, "ssidAP");
    String _passwordAP = jsonRead(configSetup, "passwordAP");
    WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
    return true;
}
