#define BLYNK_TEMPLATE_ID "TMPL6tGgogVSQ"
#define BLYNK_TEMPLATE_NAME "Final project"
#define BLYNK_AUTH_TOKEN "-C8qQaQlKbzekMhEsO7saj2p-OYBuGQJ"

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL ""
#define AUTHOR_PASSWORD ""
#define RECIPIENT_EMAIL "a"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32_MailClient.h>

const char* ssid = ""; 
const char* password = "";

#define BUZZER_PIN 26

SMTPData smtpData;
bool emailSent = false;

const char* apiUrl = ""; 

const char* class_labels[] = {"malignant", "benign", "unknown"};
float probabilities[3] = {0.0, 0.0, 0.0};

// ---------- MARIO MELODY FUNCTION ----------
void playTone(int frequency, int duration) {
  if (frequency == 0) {
    delay(duration);
  } else {
    ledcAttachPin(BUZZER_PIN, 0);
    ledcWriteTone(0, frequency);
    delay(duration);
    ledcWriteTone(0, 0);
  }
}

void playMelody() {
  int melody[] = {
    440, 440, 0, 440, 0, 349, 440, 0, 523, 0, 392, 0,
    349, 392, 0, 294, 392, 440, 415, 392, 349, 440, 523, 587,
    0, 349, 523, 440, 349, 392, 330,
    659, 659, 0, 659, 0, 523, 659, 0, 784, 0, 392, 0,
    523, 392, 0, 330, 440, 494, 466, 440, 392, 659, 784, 880,
    0, 587, 784, 659, 523, 587, 494
  };

  int noteDurations[] = {
    8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4,
    4, 8, 8, 8, 8, 8, 4,
    8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4,
    4, 8, 8, 8, 8, 8, 4
  };

  int tempo = 900;
  int melodySize = sizeof(melody) / sizeof(melody[0]);
  for (int i = 0; i < melodySize; i++) {
    int noteDuration = (tempo / noteDurations[i]);
    playTone(melody[i], noteDuration);
    delay(noteDuration * 0.3);
  }
}
// --------------------------------------------

void sendEmail(String predictionResult) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("⚠ Wi-Fi Disconnected! Cannot send email.");
        return;
    }

    if (emailSent) {
        Serial.println("📧 Email already sent. Skipping...");
        return;
    }

    smtpData.setLogin(SMTP_HOST, SMTP_PORT, AUTHOR_EMAIL, AUTHOR_PASSWORD);
    smtpData.setSender("ESP32 Skin Check", AUTHOR_EMAIL);
    smtpData.setPriority("High");
    smtpData.setSubject("Skin Check Prediction Alert");

    String message = "📢 Skin Check Alert!\n\n";
    message += "Prediction Result: " + predictionResult + "\n";
    message += "✔ If it's benign, no worries!\n";
    message += "⚠ If it's malignant, consider consulting a doctor.\n";
    message += "\n📍 Sent from ESP32";

    smtpData.setMessage(message, false);
    smtpData.addRecipient(RECIPIENT_EMAIL);

    Serial.println("📧 Attempting to send email...");

    if (!MailClient.sendMail(smtpData)) {
        Serial.print("⚠ Email failed to send. Error: ");
        Serial.println(MailClient.smtpErrorReason());
    } else {
        Serial.println("✅ Email sent successfully!");
        emailSent = true;

        // 🎵 Play melody only if benign
        if (predictionResult == "benign") {
            playMelody();
        }
    }

    smtpData.empty();
}

void setup() {
    Serial.begin(115200);
    pinMode(BUZZER_PIN, OUTPUT);
    WiFi.begin(ssid, password);
    
    Serial.println("\nConnecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\n✔ WiFi Connected!");

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
    Blynk.run();
    fetchPrediction();
    PREDICTION_WRITE();
    delay(5000);
}

void fetchPrediction() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(apiUrl);

        int httpCode = http.GET();
        if (httpCode > 0) {
            String payload = http.getString();
            Serial.println("📌 Received JSON:");
            Serial.println(payload);

            StaticJsonDocument<512> doc;
            DeserializationError error = deserializeJson(doc, payload);

            if (error) {
                Serial.println("⚠ JSON Parsing Error!");
                return;
            }

            probabilities[0] = doc["data"][0]["prediction"][0][0]; // Malignant
            probabilities[1] = doc["data"][0]["prediction"][0][1]; // Benign
            probabilities[2] = doc["data"][0]["prediction"][0][2]; // Unknown

            Serial.println("✔ Extracted Probabilities:");
            Serial.print("🔴 Malignant: "); Serial.println(probabilities[0], 4);
            Serial.print("🟢 Benign: "); Serial.println(probabilities[1], 4);
            Serial.print("🔵 Unknown: "); Serial.println(probabilities[2], 4);
        } else {
            Serial.printf("⚠ HTTP GET Request Failed: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    } else {
        Serial.println("⚠ Wi-Fi Disconnected!");
    }
}

void PREDICTION_WRITE() {
    Blynk.virtualWrite(V4, probabilities[0]);
    Blynk.virtualWrite(V0, probabilities[1]);
    Blynk.virtualWrite(V3, probabilities[2]);

    Serial.println("✔ Sent Probabilities to Blynk");

    if (probabilities[0] == 0.0 && probabilities[1] == 0.0 && probabilities[2] == 0.0) {
        Serial.println("⚠ No prediction data yet. Skipping email.");
        return;
    }

    int maxIndex = 0;
    for (int i = 1; i < 3; i++) {
        if (probabilities[i] > probabilities[maxIndex]) {
            maxIndex = i;
        }
    }

    Serial.print("📊 Highest class: ");
    Serial.println(class_labels[maxIndex]);

    if (!emailSent) {
        Serial.println("📧 Sending email with prediction...");
        sendEmail(class_labels[maxIndex]);
    } else {
        Serial.println("📧 Email already sent. Skipping.");
    }
}
