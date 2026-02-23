#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QMessageBox>
#include <QClipboard>
#include <random>
#include <string>

// Funzione per generare la password
QString generatePassword(int length, bool useUpper, bool useLower, bool useNums, bool useSyms) {
    std::string chars = "";
    if (useUpper) chars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (useLower) chars += "abcdefghijklmnopqrstuvwxyz";
    if (useNums)  chars += "0123456789";
    if (useSyms)  chars += "!@#$%^&*()_+-=[]{}|;:,.<>?/~`";

    if (chars.empty()) return "";

    std::string password = "";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, chars.size() - 1);

    for (int i = 0; i < length; ++i) {
        password += chars[dis(gen)];
    }

    return QString::fromStdString(password);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // --- TEMA OSCURO (Nero e Viola) ---
    app.setStyle("Fusion");
    QString styleSheet = R"(
        QWidget {
            background-color: #050505; /* Nero quasi assoluto */
            color: #E0E0E0; /* Bianco sporco */
            font-family: 'Segoe UI', sans-serif;
            font-size: 16px; /* Testo base più grande */
        }
        QGroupBox {
            border: 2px solid #4a148c; /* Bordo Viola Scuro */
            border-radius: 8px;
            margin-top: 1.5em;
            font-weight: bold;
            color: #b39ddb; /* Viola chiaro per il titolo */
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top center;
            padding: 0 10px;
            background-color: #050505;
        }
        QPushButton {
            background-color: #311b92; /* Viola Indaco Scuro */
            color: white;
            border: 1px solid #5e35b1;
            border-radius: 6px;
            padding: 12px;
            font-weight: bold;
            font-size: 16px;
        }
        QPushButton:hover {
            background-color: #4a148c; /* Viola più chiaro al passaggio */
            border: 1px solid #7c43bd;
        }
        QPushButton:pressed {
            background-color: #12005e; /* Molto scuro al click */
        }
        QLineEdit, QSpinBox {
            background-color: #121212; /* Grigio molto scuro */
            border: 1px solid #5e35b1;
            color: #ffffff;
            padding: 8px;
            border-radius: 4px;
            font-size: 18px;
        }
        QCheckBox {
            spacing: 10px;
            font-size: 16px;
        }
        QCheckBox::indicator {
            width: 22px;
            height: 22px;
            border: 1px solid #5e35b1;
            background: #121212;
            border-radius: 3px;
        }
        QCheckBox::indicator:checked {
            background: #673ab7; /* Viola acceso quando selezionato */
            border: 1px solid #d1c4e9;
        }
        QLabel {
            color: #e0e0e0;
        }
    )";
    app.setStyleSheet(styleSheet);

    // Finestra Principale
    QWidget window;
    window.setWindowTitle("Generatore Oscuro");
    window.resize(800, 650); // DIMENSIONI AUMENTATE (Non più microscopico)

    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    mainLayout->setSpacing(25);
    mainLayout->setContentsMargins(40, 40, 40, 40);

    // --- Titolo ---
    QLabel *titleLabel = new QLabel("🔮 GENERATORE DI PASSWORD 🔮");
    QFont titleFont = titleLabel->font();
    titleFont.setBold(true);
    titleFont.setPointSize(24); // Font molto grande
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #9575cd; margin-bottom: 10px;"); // Viola chiaro
    mainLayout->addWidget(titleLabel);

    // --- Sezione Configurazione ---
    QGroupBox *configGroup = new QGroupBox("CONFIGURAZIONE DEL SIGILLO");
    QVBoxLayout *configLayout = new QVBoxLayout(configGroup);
    configLayout->setSpacing(15);
    configLayout->setContentsMargins(20, 30, 20, 20);

    // Lunghezza
    QHBoxLayout *lengthLayout = new QHBoxLayout();
    QLabel *lblLength = new QLabel("Lunghezza Password:");
    lblLength->setStyleSheet("font-weight: bold; font-size: 18px;");
    
    QSpinBox *spinLength = new QSpinBox();
    spinLength->setRange(1, 60);
    spinLength->setValue(24); // Default più lungo
    spinLength->setMinimumWidth(120);
    
    lengthLayout->addWidget(lblLength);
    lengthLayout->addWidget(spinLength);
    configLayout->addLayout(lengthLayout);

    // Checkbox
    QCheckBox *chkUpper = new QCheckBox("Lettere Maiuscole (A-Z)");
    QCheckBox *chkLower = new QCheckBox("Lettere Minuscole (a-z)");
    QCheckBox *chkNums = new QCheckBox("Numeri (0-9)");
    QCheckBox *chkSyms = new QCheckBox("Simboli Occulti (!@#...)");
    
    chkUpper->setChecked(true);
    chkLower->setChecked(true);
    chkNums->setChecked(true);
    chkSyms->setChecked(true);

    configLayout->addWidget(chkUpper);
    configLayout->addWidget(chkLower);
    configLayout->addWidget(chkNums);
    configLayout->addWidget(chkSyms);

    mainLayout->addWidget(configGroup);

    // --- Pulsante Genera ---
    QPushButton *btnGenerate = new QPushButton("⚡ EVOCA PASSWORD ⚡");
    btnGenerate->setMinimumHeight(60); // Pulsante grande
    btnGenerate->setCursor(Qt::PointingHandCursor);
    btnGenerate->setStyleSheet("font-size: 20px; font-weight: bold; letter-spacing: 2px;");
    mainLayout->addWidget(btnGenerate);

    // --- Risultato ---
    QLineEdit *txtResult = new QLineEdit();
    txtResult->setPlaceholderText("La password apparirà qui...");
    txtResult->setReadOnly(true);
    txtResult->setAlignment(Qt::AlignCenter);
    // Stile specifico per il risultato per farlo risaltare
    txtResult->setStyleSheet("font-size: 22px; padding: 15px; color: #d1c4e9; border: 2px solid #673ab7; background-color: #1a1a1a; margin-top: 10px;");
    mainLayout->addWidget(txtResult);

    QPushButton *btnCopy = new QPushButton("Copia negli Appunti");
    btnCopy->setCursor(Qt::PointingHandCursor);
    mainLayout->addWidget(btnCopy);

    // --- Logica ---
    
    // Connetti Bottone Genera
    QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
        int len = spinLength->value();
        bool upper = chkUpper->isChecked();
        bool lower = chkLower->isChecked();
        bool nums = chkNums->isChecked();
        bool syms = chkSyms->isChecked();

        if (!upper && !lower && !nums && !syms) {
            QMessageBox::warning(&window, "Errore", "Devi selezionare almeno un tipo di carattere!");
            return;
        }

        QString pwd = generatePassword(len, upper, lower, nums, syms);
        txtResult->setText(pwd);
    });

    // Connetti Bottone Copia
    QObject::connect(btnCopy, &QPushButton::clicked, [&]() {
        QString pwd = txtResult->text();
        if (!pwd.isEmpty()) {
            QApplication::clipboard()->setText(pwd);
            QMessageBox::information(&window, "Successo", "Password copiata negli appunti!");
        }
    });

    window.show();
    return app.exec();
}
