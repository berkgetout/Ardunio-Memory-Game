#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte kalp[] = {0, 10, 31, 31, 14, 4, 0, 0};
byte sagByte[] = {0, 4, 14, 31, 31, 14, 4, 0}; // Sağ 
byte solByte[] = {0, 31, 31, 31, 31, 31, 31, 0}; // Sol 

int okunan = 0;
int kalp_x = 13;
int kalp_y = 1;
int skor = 0;
int menusecimi = 0; 
int zorlukseviyesi = 1; 
int sirauzunlugu = 3; 
volatile int zorluk;

#define sag 0
#define ust 1
#define alt 2
#define sol 3
#define secim 4
#define yok 5

int sequence[100];
int userInput[100];
int userInputIndex = 0;
int can = 3;
int xPositions[100];
int mevcutsayi = 1;
int mevcutsekil = 10;
bool secilensekil = false;


int tus_oku() {
  okunan = analogRead(0);
  if (okunan > 1000) return yok;
  if (okunan < 50) return sag;
  if (okunan < 195) return ust;
  if (okunan < 380) return alt;
  if (okunan < 555) return sol;
  if (okunan < 790) return secim;
  return yok;
}

// Ekrana kalan canları yazdırır
void yazdirKalpler() {
  for (int i = 0; i < can; i++) {
    lcd.setCursor(kalp_x - i, kalp_y);
    lcd.write(byte(1));
  }
  for (int i = can; i < 3; i++) {
    lcd.setCursor(kalp_x - i, kalp_y);
    lcd.print(" ");
  }
}

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(1, kalp);
  lcd.createChar(2, sagByte);
  lcd.createChar(3, solByte);
  randomSeed(analogRead(0));
  displayMenu();
}

void loop() {
  handleMenu();
}

// Ana menü
void displayMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-> Oyna");
  lcd.setCursor(0, 1);
  lcd.print("   Ayarlar");
  menusecimi = 0; // Menü seçimi baştan başlıyor
}

// Menüyü kontrol eder
void handleMenu() {
  int tus = tus_oku();
  switch (tus) {
    case ust:
    case alt:
      menusecimi = (menusecimi == 0) ? 1 : 0;
      lcd.setCursor(0, 0);
      lcd.print(menusecimi == 0 ? "-> Oyna    " : "   Oyna    ");
      lcd.setCursor(0, 1);
      lcd.print(menusecimi == 1 ? "-> Ayarlar " : "   Ayarlar ");
      delay(200);
      break;
    case secim:
      if (menusecimi == 0) {
        startGame();
      } else {
        displaySettings();
      }
      delay(200);
      break;
  }
}

// Ayarlar menüsü
void displaySettings() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("YAPAN:");
  lcd.setCursor(0, 1);
  lcd.print("BERK AVCI");
  delay(2000);
  lcd.clear();
  
  selectDifficulty();
}

// Zorluk seçimi
void selectDifficulty() {
  zorluk = 0;
  while (true) {
    if (zorluk > 3) zorluk = 1;
    if (zorluk < 1) zorluk = 3;
    int tus = tus_oku();
    if (tus == sag || tus == sol) {
      zorluk += (tus == sag) ? 1 : -1;
      if (zorluk > 3) zorluk = 1;
      if (zorluk < 1) zorluk = 3;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Zorluk Secin:");
      lcd.setCursor(0, 1);
      if (zorluk == 1) lcd.print("<     Kolay    >");
      if (zorluk == 2) lcd.print("<     Orta     >");
      if (zorluk == 3) lcd.print("<     Zor      >");
      delay(500);
    } else if (tus == secim) {
      zorlukseviyesi = zorluk;
      sirauzunlugu = (zorlukseviyesi == 1) ? 3 : (zorlukseviyesi == 2) ? 5 : 9;
      displayMenu();
      return;
    }
  }
}

// Oyunu başlatır
void startGame() {
  lcd.clear();
  siraolustur();
  siragoster();
  getUserInput();
}

// Rastgele bir sayı oluşturur
void siraolustur() {
  for (int i = 0; i < 100; i++) {
    int randChoice = random(0, 12); // 0-9: sayılar, 10: sağ ok, 11: sol ok
    if (randChoice < 10) {
      sequence[i] = randChoice + 1; // 1-9 arası sayılar
    } else if (randChoice == 10) {
      sequence[i] = 10; // Sağ ok
    } else {
      sequence[i] = 11; // Sol ok
    }
    xPositions[i] = random(0, 16);  // 16 sütunlu LCD ekranın x koordinatları
  }
}

// Oluşturulan sayıyı ekranda gösterir
void siragoster() {
  for (int i = 0; i < sirauzunlugu; i++) {
    lcd.clear();
    lcd.setCursor(xPositions[i], 0);
    if (sequence[i] == 10) {
      lcd.write(byte(2)); // Sağ ok
    } else if (sequence[i] == 11) {
      lcd.write(byte(3)); // Sol ok
    } else {
      lcd.print(sequence[i]);
    }
    delay(1000);
    lcd.clear();
    delay(500);
  }
  lcd.setCursor(0, 0);
  lcd.print("Sayi giriniz:");
  yazdirKalpler();
  lcd.setCursor(0, 1);
}

// Kullanıcıdan sayıyı girmesini ister
void getUserInput() {
  userInputIndex = 0;
  mevcutsayi = 1;
  secilensekil = false;
  while (userInputIndex < sirauzunlugu) {
    int tus = tus_oku();
    switch (tus) {
      case ust:
        if (!secilensekil) {
          mevcutsayi = (mevcutsayi < 9) ? mevcutsayi + 1 : 1;
          lcd.setCursor(userInputIndex, 1);
          lcd.print(mevcutsayi);
        }
        delay(200);
        break;
      case alt:
        if (!secilensekil) {
          mevcutsayi = (mevcutsayi > 1) ? mevcutsayi - 1 : 9;
          lcd.setCursor(userInputIndex, 1);
          lcd.print(mevcutsayi);
        }
        delay(200);
        break;
      case sag:
        secilensekil = true;
        mevcutsekil = (mevcutsekil == 10) ? 11 : 10; // Sağ ve sol oklar arasında geçiş
        lcd.setCursor(userInputIndex, 1);
        if (mevcutsekil == 10) {
          lcd.write(byte(2));
        } else {
          lcd.write(byte(3));
        }
        delay(200);
        break;
      case sol:
        secilensekil = true;
        mevcutsekil = (mevcutsekil == 10) ? 11 : 10; // Sağ ve sol oklar arasında geçiş
        lcd.setCursor(userInputIndex, 1);
        if (mevcutsekil == 10) {
          lcd.write(byte(2));
        } else {
          lcd.write(byte(3));
        }
        delay(200);
        break;
      case secim:
        if (secilensekil) {
          userInput[userInputIndex++] = mevcutsekil;
        } else {
          userInput[userInputIndex++] = mevcutsayi;
        }
        mevcutsayi = 1;
        mevcutsekil = 10;
        secilensekil = false;
        delay(200);
        break;
    }
  }
  checkUserInput();
}

// sayı karşılaştırma
void checkUserInput() {
  bool isCorrect = true;
  for (int i = 0; i < sirauzunlugu; i++) {
    if (userInput[i] != sequence[i]) {
      isCorrect = false;
      break;
    }
  }

  if (isCorrect) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DOGRU!");
    delay(2000);
    sirauzunlugu++;
    startGame();
  } else {
    can--;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Yanlis girdiniz");
    yazdirKalpler();
    delay(2000);
    if (can > 0) {
      startGame();
    } else {
      Oyunbitisi();
    }
  }
}

// Oyun bittiğinde ekranda mesaj gösterir
void Oyunbitisi() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Oyun Bitti");
  delay(2000);
  TekrarOynaMenu();
}

// Oyun bittiğinde yeniden başlatma menüsünü gösterir
void TekrarOynaMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-> Tekrar Oyna");
  lcd.setCursor(0, 1);
  lcd.print("   Cikis");
  menusecimi = 0; // Menü seçimi baştan başlıyor

  while (true) {
    int tus = tus_oku();
    switch (tus) {
      case ust:
      case alt:
        menusecimi = (menusecimi == 0) ? 1 : 0;
        
        lcd.setCursor(0, 0);
        lcd.print(menusecimi == 0 ? "-> Tekrar Oyna" : "   Tekrar Oyna");
        lcd.setCursor(0, 1);
        lcd.print(menusecimi == 1 ? "-> Cikis     " : "   Cikis     ");
        delay(200);
        break;
      case secim:
        if (menusecimi == 0) {
          OyunuSifirla();
          startGame();
        } else {
          displayMenu();
          return;  // Ana menüye dönmek için return kullan
        }
        delay(200);
        break;
    }
  }
}

// Oyunu sıfırlar
void OyunuSifirla() {
  sirauzunlugu = (zorlukseviyesi == 1) ? 3 : (zorlukseviyesi == 2) ? 5 : 9;
  can = 3;
  skor = 0;
  yazdirKalpler();
  displayMenu();
}

