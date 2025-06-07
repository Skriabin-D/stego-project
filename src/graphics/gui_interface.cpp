#include "graphics/gui_interface.hpp" 

void handleEmbedding(const QString& imagePath, const QString& message, const QString& savePath, bool usePVD)
{
    auto bits = stringToBitSequence(message.toStdString());
    auto encoded = encodeBitSequence(bits);
    if (usePVD)
        embed_pvd(imagePath.toStdString(), encoded, savePath.toStdString());
    else
        embed_lsb_dct(imagePath.toStdString(), encoded, savePath.toStdString());

    QMessageBox::information(nullptr, "Готово", "Сообщение встроено методом " + (usePVD ? "PVD" : "LSB-DCT"));
}

void handleExtraction(const QString& imagePath, size_t numBits, bool usePVD, QTextEdit* outputText)
{
    std::vector<uint8_t> bits;
    if (usePVD)
        bits = extract_pvd(imagePath.toStdString(), numBits);
    else
        bits = extract_lsb_dct(imagePath.toStdString(), numBits);

    if (bits.empty()) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось извлечь сообщение.");
        return;
    }

    auto decoded = decodeBitSequence(bits);
    auto message = bitSequenceToString(decoded);

    outputText->setPlainText(QString::fromStdString(message));
    QMessageBox::information(nullptr, "Готово", "Сообщение успешно извлечено.");
}
