#include <iostream>

using namespace std;

#include <cmath>

struct Pixel {  //脚点数据
    double x, y, z, g;
    bool flag;
};

struct List { //数据链表
    Pixel *pixel;
    List *next;
};

struct Line { //三角形边
    Pixel *pixel1;  //三角形边一端点
    Pixel *pixel2;  //三角形边另一端点
    Pixel *pixel3;  //三角形边所对顶点
    bool flag;
};

struct Linelist { //三角形边表
    Line *line;
    Linelist *next;
};

struct Triangle { //三角形表
    Line *line1;
    Line *line2;
    Line *line3;
    Triangle *next;
};


//以下是程序中关于建网的部分：
// DelaunayTIN.cpp: implementation of the CDelaunayTIN class.
//
//////////////////////////////////////////////////////////////////////
//功能：   用给定的数据链表数据，组建Delaunay不规则三角网
//输入参数：数据链表list;区域范围(XMin,YMin),(XMax,YMax)
//输出参数：不规则三角网首三角形地址


Triangle *CSimRegular::CreateDelaunayTIN(List *list) {
    //组建第一个三角形
    List *node;
    Pixel *pt1, *pt2, *pt3;
    bool flag;
    Triangle *TIN;
    pt1 = list->pixel;
    pt2 = list->next->pixel;
    node = list->next->next;
    while(node != NULL) {
        if(
            (pt1->x - node->pixel->x) * (pt1->x - node->pixel->x) + (pt1->y - node->pixel->y) * (pt1->y - node->pixel->y)
            < (pt1->x - pt2->x) * (pt1->x - pt2->x) + (pt1->y - pt2->y) * (pt1->y - pt2->y)
        ) {
            pt2 = node->pixel;
        }
        node = node->next;

        node = list->next;
        pt3 = NULL;
        while(node != NULL) {
            if(node->pixel == pt1 || node->pixel == pt2) {
                node = node->next;
                continue;
            }

            if(pt3 == NULL) {
                pt3 = node->pixel;
            } else {
                float dist11 = sqrt((pt1->x - node->pixel->x) * (pt1->x - node->pixel->x) + (pt1->y - node->pixel->y) * (pt1->y - node->pixel->y));
                float dist12 = sqrt((pt2->x - node->pixel->x) * (pt2->x - node->pixel->x) + (pt2->y - node->pixel->y) * (pt2->y - node->pixel->y));
                float dist12_3 = sqrt((pt1->x - pt2->x) * (pt1->x - pt2->x) + (pt1->y - pt2->y) * (pt1->y - pt2->y));
                float dist21 = sqrt((pt1->x - pt3->x) * (pt1->x - pt3->x) + (pt1->y - pt3->y) * (pt1->y - pt3->y));
                float dist22 = sqrt((pt3->x - pt2->x) * (pt3->x - pt2->x) + (pt3->y - pt2->y) * (pt3->y - pt2->y));
                if((pow(dist11, 2) + pow(dist12, 2) - pow(dist12_3, 2)) / (2 * dist11 * dist12)
                        < (pow(dist21, 2) + pow(dist22, 2) - pow(dist12_3, 2)) / (2 * dist21 * dist22)) //余弦判断角度

                {
                    pt3 = node->pixel;
                }
            }
            node = node->next;

            //LineList
            Linelist *linehead, *linenode, *linelast;
            Line *ln1, *ln2, *ln3;
            linenode = new Linelist;
            linenode->line = new Line;
            linenode->line->pixel1 = pt1;
            linenode->line->pixel2 = pt2;
            linenode->line->pixel3 = pt3;
            linenode->line->flag = false;
            linenode->next = NULL;
            linehead = linelast = linenode;
            ln1 = linenode->line;
            linenode = new Linelist;
            linenode->line = new Line;
            linenode->line->pixel1 = pt2;
            linenode->line->pixel2 = pt3;
            linenode->line->pixel3 = pt1;
            linenode->line->flag = false;
            linenode->next = NULL;
            linelast->next = linenode;
            linelast = linenode;
            ln2 = linenode->line;
            linenode = new Linelist;
            linenode->line = new Line;
            linenode->line->pixel1 = pt3;
            linenode->line->pixel2 = pt1;
            linenode->line->pixel3 = pt2;
            linenode->line->flag = false;
            linenode->next = NULL;
            linelast->next = linenode;
            linelast = linenode;
            ln3 = linenode->line;
            //first Triangle
            Triangle *tglhead, *tglnode, *tgllast;
            tglnode = new Triangle;
            tglnode->line1 = ln1;
            tglnode->line2 = ln2;
            tglnode->line3 = ln3;
            tglnode->next = NULL;
            tglhead = tgllast = tglnode;


            //expend tin;
            Linelist *linetmp, *linetemp;
            List *pixeltmp;
            float x1, y1, x2, y2, x3, y3;
            linetmp = linehead;
            while(linetmp != NULL) {
                if(linetmp->line->flag == true) {
                    linetmp = linetmp->next;
                    continue;
                }
                ln1 = linetmp->line;
                pt1 = linetmp->line->pixel1;
                pt2 = linetmp->line->pixel2;
                x1 = linetmp->line->pixel1->x;
                y1 = linetmp->line->pixel1->y;
                x2 = linetmp->line->pixel2->x;
                y2 = linetmp->line->pixel2->y;
                x3 = linetmp->line->pixel3->x;
                y3 = linetmp->line->pixel3->y;


                pixeltmp = list;
                pt3 = NULL;
                while(pixeltmp != NULL) {
                    if(pixeltmp->pixel == pt1 || pixeltmp->pixel == pt2) {
                        pixeltmp = pixeltmp->next;
                        continue;
                    }
                    if(((y2 - y1)*pixeltmp->pixel->x + (x1 - x2)*pixeltmp->pixel->y + (x2 * y1 - x1 * y2))
                            * ((y2 - y1)*x3 + (x1 - x2)*y3 + (x2 * y1 - x1 * y2)) >= 0) {
                        pixeltmp = pixeltmp->next;
                        continue;
                    }


                    if(pt3 == NULL)pt3 = pixeltmp->pixel;
                    else {
                        float dist11 = sqrt((pt1->x - pixeltmp->pixel->x) * (pt1->x - pixeltmp->pixel->x) + (pt1->y - pixeltmp->pixel->y) * (pt1->y - pixeltmp->pixel->y));
                        float dist12 = sqrt((pt2->x - pixeltmp->pixel->x) * (pt2->x - pixeltmp->pixel->x) + (pt2->y - pixeltmp->pixel->y) * (pt2->y - pixeltmp->pixel->y));
                        float dist12_3 = sqrt((pt1->x - pt2->x) * (pt1->x - pt2->x) + (pt1->y - pt2->y) * (pt1->y - pt2->y));
                        float dist21 = sqrt((pt1->x - pt3->x) * (pt1->x - pt3->x) + (pt1->y - pt3->y) * (pt1->y - pt3->y));
                        float dist22 = sqrt((pt3->x - pt2->x) * (pt3->x - pt2->x) + (pt3->y - pt2->y) * (pt3->y - pt2->y));
                        if((pow(dist11, 2.0) + pow(dist12, 2.0) - pow(dist12_3, 2)) / (2 * dist11 * dist12)
                                < (pow(dist21, 2) + pow(dist22, 2) - pow(dist12_3, 2)) / (2 * dist21 * dist22)) { //余弦判断角度
                            pt3 = pixeltmp->pixel;
                        }
                    }
                    pixeltmp = pixeltmp->next;
                }
                if(pt3 != NULL) {
                    linetemp = linehead;
                    flag = false;
                    while(linetemp != NULL) {
                        if((pt1 == linetemp->line->pixel1 && pt3 == linetemp->line->pixel2)
                                || (pt3 == linetemp->line->pixel1 && pt1 == linetemp->line->pixel2)) {
                            linetemp->line->flag = true;
                            flag = true;
                            ln2 = linetemp->line;
                            break;
                        }
                        linetemp = linetemp->next;
                    }
                    if(!flag) {
                        linenode = new Linelist;
                        linenode->line = new Line;
                        linenode->line->pixel1 = pt3;
                        linenode->line->pixel2 = pt1;
                        linenode->line->pixel3 = pt2;
                        linenode->line->flag = false;
                        linenode->next = NULL;
                        linelast->next = linenode;
                        linelast = linenode;
                        ln2 = linenode->line;
                    }
                    linetemp = linehead;
                    flag = false;
                    while(linetemp != NULL) {
                        if((pt2 == linetemp->line->pixel1 && pt3 == linetemp->line->pixel2)
                                || (pt3 == linetemp->line->pixel1 && pt2 == linetemp->line->pixel2)) {
                            linetemp->line->flag = true;
                            flag = true;
                            ln3 = linetemp->line;
                            break;
                        }
                        linetemp = linetemp->next;
                    }
                    if(!flag) {
                        linenode = new Linelist;
                        linenode->line = new Line;
                        linenode->line->pixel1 = pt2;
                        linenode->line->pixel2 = pt3;
                        linenode->line->pixel3 = pt1;
                        linenode->line->flag = false;
                        linenode->next = NULL;
                        linelast->next = linenode;
                        linelast = linenode;
                        ln3 = linenode->line;
                    }
                    tglnode = new Triangle;
                    tglnode->line1 = ln1;
                    tglnode->line2 = ln2;
                    tglnode->line3 = ln3;
                    tglnode->next = NULL;
                    tgllast->next = tglnode;
                    tgllast = tglnode;
                }


                linetmp->line->flag = true;
                linetmp = linetmp->next;
            }
            TIN = tglhead;
            return TIN;
        }
        return NULL;
    }
    return NULL;
}

int main() {

    return 0;
}