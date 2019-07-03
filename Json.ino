// ------------- Чтение значения json
String jsonRead(String &json, String name) {
    DynamicJsonDocument jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    return root[name].as<String>();
}

// ------------- Чтение значения json
int jsonReadtoInt(String &json, String name) {
    DynamicJsonDocument jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    return root[name];
}

// ------------- Запись значения json String
String jsonWrite(String &json, String name, String volume) {
    DynamicJsonDocument jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    root[name] = volume;
    json = "";
    root.printTo(json);
    return json;
}

// ------------- Запись значения json int
String jsonWrite(String &json, String name, int volume) {
    DynamicJsonDocument jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    root[name] = volume;
    json = "";
    root.printTo(json);
    return json;
}

// ------------- Запись значения json float
String jsonWrite(String &json, String name, float volume) {
    DynamicJsonDocument jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    root[name] = volume;
    json = "";
    root.printTo(json);
    return json;
}

void saveConfig () {
    writeFile("config.json", configSetup );
}

// ------------- Чтение файла в строку
String readFile(String fileName, size_t len ) {
    File configFile = SPIFFS.open("/" + fileName, "r");
    if (!configFile) {
        return "Failed";
    }
    size_t size = configFile.size();
    if (size > len) {
        configFile.close();
        return "Large";
    }
    String temp = configFile.readString();
    configFile.close();
    return temp;
}

// ------------- Запись строки в файл
String writeFile(String fileName, String strings ) {
    File configFile = SPIFFS.open("/" + fileName, "w");
    if (!configFile) {
        return "Failed to open config file";
    }
    configFile.print(strings);
    //strings.printTo(configFile);
    configFile.close();
    return "Ok";
}

// ------------- Отправить данные в Options String ------------------------------
void sendOptions(String Name, String volume) {
    jsonWrite(configOptions, Name, volume);
}
// ------------- Отправить данные в Options int -----------------------
void sendOptions(String Name, int volume) {
    jsonWrite(configOptions, Name, volume);
}



/*
// --------------------Выделяем строку до маркера --------------------------------------------------
String selectToMarker (String str, String found) {
    int p = str.indexOf(found);
    return str.substring(0, p);
}

// -------------------Выделяем строку от конца строки до маркера ---------------------
String selectToMarkerLast (String str, String found) {
    int p = str.lastIndexOf(found);
    return str.substring(p + found.length());
}

//----------------------Удаляем все до символа разделителя -----------------
String deleteBeforeDelimiter(String str, String found) {
    int p = str.indexOf(found) + found.length();
    return str.substring(p);
}
//----------------------Удаляем все до символа разделителя -----------------
String deleteBeforeDelimiterTo(String str, String found) {
    int p = str.indexOf(found);
    return str.substring(p);
}
// -------------------Удаляем строку от конца строки до маркера ---------------------
String deleteToMarkerLast (String str, String found) {
    int p = str.lastIndexOf(found);
    return str.substring(0, p);
}
*/