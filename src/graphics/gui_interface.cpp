#include "graphics/gui_interface.hpp" 

void handleEmbedding(const QString& imagePath, const QString& message, const QString& savePath, bool usePVD)
{
    auto bits = stringToBitSequence(message.toStdString());
    auto encoded = encodeBitSequence(bits);
    size_t size;
    if (usePVD)
       size = embed_pvd(imagePath.toStdString(), encoded, savePath.toStdString());
    else
       size = embed_lsb_dct(imagePath.toStdString(), encoded, savePath.toStdString());
    QString method = usePVD ? "PVD" : "LSB-DCT";
    QString num_bits = QString::number(size);
    QMessageBox::information(nullptr, u8"Ready", u8"Message was embedded using the method: " + method + u8"\nTHE NUMBER OF BITS EMBEDDED: " + num_bits);
}

void handleExtraction(const QString& imagePath, size_t numBits, bool usePVD, QTextEdit* outputText)
{
    std::vector<uint8_t> bits;
    if (usePVD)
        bits = extract_pvd(imagePath.toStdString(), numBits);
    else
        bits = extract_lsb_dct(imagePath.toStdString(), numBits);

    if (bits.empty()) {
        QMessageBox::warning(nullptr, u8"Error", u8"It was impossible to extract the message.");
        return;
    }

    auto decoded = decodeBitSequence(bits);
    auto message = bitSequenceToString(decoded);

    outputText->setPlainText(QString::fromStdString(message));
    QMessageBox::information(nullptr, u8"Ready", u8"The message was successfully extracted.");
}
