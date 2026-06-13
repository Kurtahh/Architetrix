#include "Renderer.h"
#include "../piece/FallingPiece.h"
#include "../piece/Piece.h"
#include <iostream>

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
                            std::cout << "\033[1m1\033[0m";
                        else
                            std::cout << "\033[2m░\033[0m";  // dim ghost
                    } else if (hasBit) {
                        if (isPieceRow) {
                            std::cout << "\033[1m0\033[0m";
                            } else if (isGhostRow) {
                                std::cout << "\033[2m░\033[0m";
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

            std::cout << opLabel(row.op) << " |";

            const std::vector<bool>* pieceBits = (isPieceRow || isGhostRow) ? &piece->getBits() : nullptr;
            int pieceCol = (isPieceRow || isGhostRow) ? piece->getCol() : -1;

            for (int c = 0; c < Board::WIDTH; ++c) {
                int pIdx = c - pieceCol;
                bool hasPieceBit = pieceBits &&
                                   pIdx >= 0 &&
                                   pIdx < static_cast<int>(pieceBits->size()) &&
                                   (*pieceBits)[pIdx];

                if (hasPieceBit && isPieceRow) {
                    std::cout << "\033[1m1\033[0m";
                } else if (hasPieceBit && isGhostRow) {
                    std::cout << "\033[2m░\033[0m";
                } else {
                    bool bit = c < static_cast<int>(row.bits.size()) && row.bits[c];
                    std::cout << (bit ? '1' : '.');
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
        std::cout << "Hold:  ";
        for (bool b : held->getBits()) 
            std::cout << (b ? '1' : '0');
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