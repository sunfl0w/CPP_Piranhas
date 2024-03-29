#include "AI/Evaluation/UniformityEvaluation.hpp"

using namespace AI::Evaluation;
using namespace Piranhas;

UniformityEvaluation::UniformityEvaluation() {}

float UniformityEvaluation::GetAreaCheckersCover(const std::vector<Field> &checkers) {
    int lowX = 0, upX = 0, lowY = 0, upY = 0;
    for (Field field : checkers) {
        if (field.position.x < lowX) {
            lowX = field.position.x;
        }
        if (field.position.y < lowY) {
            lowY = field.position.y;
        }
        if (field.position.x > upX) {
            upX = field.position.x;
        }
        if (field.position.y > upY) {
            upY = field.position.y;
        }
    }

    int width = upX - lowX + 1;
    int height = upY - lowY + 1;
    float area = width * height;
    return area;
}

float UniformityEvaluation::Evaluate(const std::vector<Field> &checkers) {
    return 1.0f / GetAreaCheckersCover(checkers);
}