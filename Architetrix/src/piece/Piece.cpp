#include "Piece.h"

Piece::Piece(std::vector<std::vector<bool>> bits)
    : bits_(std::move(bits))
{
    height_ = static_cast<int>(bits_.size());
    width_  = height_ > 0 ? static_cast<int>(bits_[0].size()) : 0;
}

const std::vector<std::vector<bool>>& Piece::getBits2D() const { 
    return bits_;
}

std::vector<bool> Piece::getBits() const {
    std::vector<bool> flat;
    for (const auto& row : bits_)
        for (bool b : row)
            flat.push_back(b);
    return flat;
}

std::vector<std::vector<bool>> Piece::getRows() const {
    return bits_;
}

std::vector<std::vector<bool>>& Piece::getRowsRef() {
    return bits_;
}

int Piece::getWidth() const { 
    return width_; 
}

int Piece::getHeight() const { 
    return height_; 
}

std::string Piece::toString() const {
    std::stringstream ss;
    for (const auto& row : bits_) {
        for (bool bit : row) {
            ss << (bit ? '1' : '0');
        }
        ss << '\n';
    }
    return ss.str();
}

std::string Piece::toDebugString() const {
    std::stringstream ss;
    ss << width_ << " " << height_;
    return ss.str();
}