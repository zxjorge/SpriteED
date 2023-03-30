#include "tool.h"

Tool::Tool() :
    brushPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)),
    selectedToolType(ToolType::BRUSH)
{

}

void Tool::setColor(QColor color){
    brushPen.setColor(color);
}

void Tool::setBrushSize(int size){
    brushPen.setWidth(size);
}

void Tool::setSelectedToolType(ToolType type){
    selectedToolType = type;
}


void fillImageAtPosition(QImage* image, QPoint point){

}


QPen Tool::getBrushPen(){
    return brushPen;
}

ToolType Tool::getSelectedToolType() {
    return selectedToolType;
}

QPen Tool::getAirBrushPen() {
    QPen pen = brushPen;

    // TODO Random texture for pen

    return pen;
}

QPen Tool::getErasePen() {
    QPen erasePen = brushPen;
    erasePen.setColor(Qt::white);
    return erasePen;
}




