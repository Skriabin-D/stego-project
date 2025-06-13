#pragma once
#include "encoding/Hamming.hpp"
#include "embedding_extracting/pvd.hpp"
#include "embedding_extracting/lsb_dct.hpp"

#include <QMessageBox>
#include <QTextEdit>
#include <QString>



/**
 * @file gui_interface.hpp
 * @brief GUI helper functions to connect embedding/extraction logic.
 *
 * Defines handleEmbedding() and handleExtraction() which bridge the Qt UI
 * with the underlying steganography algorithms.
 */
#pragma once



/**
 * @brief Embed a text message into an image and save the stego-image.
 *
 * This function takes the user’s message, converts it into a bit sequence
 * (with Hamming error-correction codes), then chooses one of two embedding
 * algorithms—PVD or LSB-DCT—based on @p usePVD. It writes the resulting
 * stego-image to @p savePath, and shows an information box telling the user
 * which method was used and how many bits were embedded.
 *
 * @param imagePath   Path to the cover image file (where to hide data).
 * @param message     The text string to embed.
 * @param savePath    Path where the resulting stego-image will be saved.
 * @param usePVD      If true, use the \(PVD\) algorithm; if false, use \(LSB\)-DCT.
 */
void handleEmbedding(const QString& imagePath, const QString& message, const QString& savePath, bool usePVD);





/**
 * @brief Extract a hidden text message from a stego-image.
 *
 * Opens the stego-image at @p imagePath and extracts up to @p numBits bits
 * using the chosen algorithm (PVD or LSB-DCT). If extraction fails or
 * yields no data, a warning box is shown instead.
 *
 * @param imagePath   Path to the stego-image containing hidden data.
 * @param numBits     Number of bits to attempt to extract.
 * @param usePVD      If true, use the \(PVD\) extraction method; if false, use \(LSB\)-DCT.
 * @param outputText  Pointer to a QTextEdit where the extracted message will be displayed.
 */
void handleExtraction(const QString& imagePath, size_t numBits, bool usePVD, QTextEdit* outputText);