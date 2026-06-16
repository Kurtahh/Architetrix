#include "Renderer.h"
#include "../piece/FallingPiece.h"
#include "../piece/Piece.h"
#include <iostream>
#include <thread>
#include <chrono>

// ANSI color codes
const std::string Renderer::RESET = "\033[0m";

// Color definitions for operators
static const std::string COLOR_AND = "\033[34m"; // Blue
static const std::string COLOR_OR = "\033[32m"; // Green
static const std::string COLOR_XOR = "\033[33m"; // Yellow
static const std::string COLOR_NAND = "\033[31m"; // Red
static const std::string COLOR_NOR = "\033[35m"; // Magenta
static const std::string COLOR_XNOR = "\033[36m"; // Cyan

static const std::string COLOR_HELD = "\033[1;33m"; // Bright Yellow for held piece
static const std::string COLOR_FALLING = "\033[1;32m"; // Bright Green for falling piece
static const std::string COLOR_GHOST = "\033[32m"; // Green for ghost piece (dimmer)
static const std::string COLOR_FLASH = "\033[1;37m"; // Bright White for flash effect

std::string Renderer::getOpColor(Board::Operator op) {
    switch (op) {
        case Board::Operator::AND: 
            return COLOR_AND;
        case Board::Operator::OR: 
            return COLOR_OR;
        case Board::Operator::XOR: 
            return COLOR_XOR;
        case Board::Operator::NAND: 
            return COLOR_NAND;
        case Board::Operator::NOR: 
            return COLOR_NOR;
        case Board::Operator::XNOR: 
            return COLOR_XNOR;
        default: 
            return Renderer::RESET;
    }
}

void Renderer::draw(const Board& board,
                    const FallingPiece* fallingPiece,
                    const Piece* upcomingPiece,
                    const Piece* heldPiece,
                    int score,
                    int level,
                    int rowAddTimeRemainingMs,
                    int personalRecord) const {
    clearScreen();
    drawBoard(board, fallingPiece);
    drawSidebar(upcomingPiece, heldPiece, score, level, rowAddTimeRemainingMs, personalRecord);
    std::cout << std::flush;
}

void Renderer::flashClearRows(const std::vector<Board::Row>& rowsBeforeClear,
                              const std::vector<int>& clearedRowIndices,
                              const Piece* upcomingPiece,
                              const Piece* heldPiece,
                              int score,
                              int level,
                              int personalRecord) const {
    if (clearedRowIndices.empty()) return;

    int stackTop = Board::VISIBLE_HEIGHT - static_cast<int>(rowsBeforeClear.size());

    // Animation: 4 flashes with simple symbols - cleared rows turn white and bright
    const char* symbols[] = {"#", "=", "~", "+"};
    
    for (int flash = 0; flash < 4; ++flash) {
        // Redraw the full screen (board + sidebar)
        clearScreen();
        
        for (int visRow = 0; visRow < Board::VISIBLE_HEIGHT; ++visRow) {
            std::cout << "\r\033[2K";

            if (visRow < stackTop) {
                std::cout << "     |                |\n";
            } else {
                int stackIndex = visRow - stackTop;
                
                if (stackIndex >= static_cast<int>(rowsBeforeClear.size())) {
                    std::cout << "     |                |\n";
                    continue;
                }
                
                const Board::Row& row = rowsBeforeClear[stackIndex];
                
                // Check if this row is being cleared
                bool isCleared = false;
                for (int clearedIdx : clearedRowIndices) {
                    if (clearedIdx == stackIndex) {
                        isCleared = true;
                        break;
                    }
                }

                // Operator label: use bright white if cleared, otherwise normal color
                if (isCleared) {
                    std::cout << "\033[1;37m" << opLabel(row.op) << RESET;  // Bright white
                } else {
                    std::cout << getOpColor(row.op) << opLabel(row.op) << RESET;
                }
                std::cout << " |";

                // Draw the row bits
                for (int c = 0; c < Board::WIDTH; ++c) {
                    // Safely access bits, treating out-of-bounds as false
                    bool bit = false;
                    if (c < static_cast<int>(row.bits.size())) {
                        bit = row.bits[c];
                    }
                    
                    if (isCleared) {
                        // Cleared row: flash white with symbols
                        if (bit) {
                            std::cout << "\033[1;37m" << symbols[flash] << RESET;
                        } else {
                            std::cout << "\033[1;37m" << symbols[flash] << RESET;
                        }
                    } else {
                        // Normal row: use operator color (never changes during animation)
                        std::string opColor = getOpColor(row.op);
                        if (bit) {
                            std::cout << opColor << "1" << RESET;
                        } else {
                            std::cout << opColor << "." << RESET;
                        }
                    }
                }
                std::cout << "|\n";
            }
        }
        
        // Draw sidebar
        std::cout << "\r\033[2K" << "Score: " << score << "   Level: " << level << "  Highscore: " << personalRecord << "\n";
        std::cout << "\r\033[2K";
        if (upcomingPiece) {
            std::cout << "Next:  ";
            for (bool b : upcomingPiece->getBits()) 
                std::cout << (b ? '1' : '0');
        }
        std::cout << "\n";
        std::cout << "\r\033[2K";
        if (heldPiece) {
            std::cout << "Hold:  " << COLOR_HELD;
            for (bool b : heldPiece->getBits()) 
                std::cout << (b ? '1' : '0');
            std::cout << RESET;
        }
        std::cout << "\n";
        std::cout << "\r\033[2K" << "Next row in: 0s\n";
        
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void Renderer::drawBoard(const Board& board, const FallingPiece* piece) const {
    const auto& rows = board.getRows();
    int stackTop = Board::VISIBLE_HEIGHT - board.getHeight();

    int ghostRow = piece ? piece->getGhostRow(board) : -1;

    for (int visRow = 0; visRow < Board::VISIBLE_HEIGHT; ++visRow) {
        std::cout << "\r\033[2K";

        if (visRow < stackTop) {
            bool isPieceRow = piece && piece->getRow() == visRow;
            bool isGhostRow = piece && ghostRow == visRow && !isPieceRow;

            if (isPieceRow || isGhostRow) {
                std::cout << "     |";
                const auto& pieceBits = piece->getBits();
                int pieceCol = piece->getCol();
                for (int c = 0; c < Board::WIDTH; ++c) {
                    int pIdx = c - pieceCol;
                    bool hasBit = pIdx >= 0 && pIdx < static_cast<int>(pieceBits.size());
                    if (hasBit && pieceBits[pIdx]) {
                        if (isPieceRow)
                            std::cout << COLOR_FALLING << "1" << RESET;
                        else
                            std::cout << COLOR_GHOST << "░" << RESET;  // ghost in green
                    } else if (hasBit) {
                        if (isPieceRow) {
                            std::cout << COLOR_FALLING << "0" << RESET;
                        } else if (isGhostRow) {
                            std::cout << COLOR_GHOST << "░" << RESET;
                        } else {
                            std::cout << ' ';
                        }
                    } else {
                        std::cout << ' ';
                    }
                }
                std::cout << "|\n";
            } else {
                std::cout << "     |                |\n";
            }
        } else {
            int stackIndex = visRow - stackTop;
            const Board::Row& row = rows[stackIndex];
            const bool isPieceRow = piece && piece->getRow() == visRow;
            const bool isGhostRow = piece && ghostRow == visRow && !isPieceRow;

            // Color-code the operator label
            std::string opColor = getOpColor(row.op);
            std::cout << opColor << opLabel(row.op) << RESET << " |";

            const std::vector<bool>* pieceBits = (isPieceRow || isGhostRow) ? &piece->getBits() : nullptr;
            int pieceCol = (isPieceRow || isGhostRow) ? piece->getCol() : -1;

            for (int c = 0; c < Board::WIDTH; ++c) {
                int pIdx = c - pieceCol;
                bool hasPieceBit = pieceBits &&
                                   pIdx >= 0 &&
                                   pIdx < static_cast<int>(pieceBits->size()) &&
                                   (*pieceBits)[pIdx];

                if (hasPieceBit && isPieceRow) {
                    std::cout << COLOR_FALLING << "1" << RESET;
                } else if (hasPieceBit && isGhostRow) {
                    std::cout << COLOR_GHOST << "░" << RESET;
                } else {
                    bool bit = c < static_cast<int>(row.bits.size()) && row.bits[c];
                    if (bit) {
                        std::cout << opColor << "1" << RESET;
                    } else {
                        std::cout << opColor << "." << RESET;
                    }
                }
            }
            std::cout << "|\n";
        }
    }
}

void Renderer::drawSidebar(const Piece* upcoming, const Piece* held, int score, int level, int rowAddTimeRemainingMs, int personalRecord) const {
    std::cout << "\r\033[2K" << "Score: " << score << "   Level: " << level << "  Highscore: " << personalRecord << "\n";
    std::cout << "\r\033[2K";
    if (upcoming) {
        std::cout << "Next:  ";
        for (bool b : upcoming->getBits()) 
            std::cout << (b ? '1' : '0');
    }
    std::cout << "\n";
    std::cout << "\r\033[2K";
    if (held) {
        // Highlight held piece in bright yellow with background
        std::cout << "Hold:  " << COLOR_HELD;
        for (bool b : held->getBits()) 
            std::cout << (b ? '1' : '0');
        std::cout << RESET;
    }
    std::cout << "\n";
    std::cout << "\r\033[2K" << "Next row in: " << (rowAddTimeRemainingMs / 1000) << "s\n";
}

std::string Renderer::opLabel(Board::Operator op) {
    switch (op) {
        case Board::Operator::AND:  
            return " AND";
        case Board::Operator::OR:   
            return "  OR";
        case Board::Operator::XOR:  
            return " XOR";
        case Board::Operator::NAND: 
            return "NAND";
        case Board::Operator::NOR:  
            return " NOR";
        case Board::Operator::XNOR: 
            return "XNOR";
        default: 
            return "  ??";
    }
}

void Renderer::clearScreen() { 
    std::cout << "\033[2J\033[H"; 
}

void Renderer::moveCursorHome() { 
    std::cout << "\033[H"; 
}

void Renderer::displayGameOver(int score, int level, int personalRecord, bool newRecord) const {
    // Flashy game over animation
    const char* patterns[] = {"#", "=", "~", "+", "*", "X"};
    
    for (int iteration = 0; iteration < 6; ++iteration) {
        clearScreen();
        
        // Print centered GAME OVER with flashing colors
        std::string colors[] = {"\033[1;31m", "\033[1;33m", "\033[1;36m", "\033[1;35m"};
        std::string color = colors[iteration % 4];
        
        // Top border
        std::cout << color;
        for (int i = 0; i < 50; ++i) std::cout << patterns[iteration % 6];
        std::cout << RESET << "\n\n";
        
        // GAME OVER text
        std::cout << color << "\033[1m";
        std::cout << "                     GAME OVER\n";
        std::cout << RESET << "\n";
        
        // Stats
        std::cout << color << "Final Score: " << RESET << score << "\n";
        std::cout << color << "Level Reached: " << RESET << level << "\n";
        
        if (newRecord) {
            std::cout << "\033[1;33m*** NEW HIGHSCORE ***" << RESET << " " << personalRecord << "\n";
        } else {
            std::cout << color << "Highscore: " << RESET << personalRecord << "\n";
        }
        
        std::cout << "\n";
        
        // Bottom border
        std::cout << color;
        for (int i = 0; i < 50; ++i) std::cout << patterns[iteration % 6];
        std::cout << RESET << "\n";
        
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    
    // Final display (static)
    clearScreen();
    std::cout << "\033[1;37m";
    for (int i = 0; i < 50; ++i) std::cout << "=";
    std::cout << RESET << "\n\n";
    
    std::cout << "\033[1;31m" << "                     GAME OVER" << RESET << "\n\n";
    
    std::cout << "Final Score: " << score << "\n";
    std::cout << "Level Reached: " << level << "\n";
    
    if (newRecord) {
        std::cout << "\033[1;33m*** NEW HIGHSCORE: " << personalRecord << " ***" << RESET << "\n";
    } else {
        std::cout << "Highscore: " << personalRecord << "\n";
    }
    
    std::cout << "\n";
    std::cout << "\033[1;37m";
    for (int i = 0; i < 50; ++i) std::cout << "=";
    std::cout << RESET << "\n";
    std::cout << std::flush;
}