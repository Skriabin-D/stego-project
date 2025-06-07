#pragma once
#include "encoding/Hamming.hpp"
#include "embedding_extracting/pvd.hpp"
#include "embedding_extracting/lsb_dct.hpp"

#include <QMessageBox>
#include <QTextEdit>
#include <QString>

void handleEmbedding(const QString& imagePath, const QString& message, const QString& savePath, bool usePVD);

void handleExtraction(const QString& imagePath, size_t numBits, bool usePVD, QTextEdit* outputText);