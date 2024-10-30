/*
 * This file is part of the DSView project.
 * DSView is based on PulseView.
 *
 * Copyright (C) 2016 DreamSourceLab <support@dreamsourcelab.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef DSVIEW_PV_TOOLBARS_TITLEBAR_H
#define DSVIEW_PV_TOOLBARS_TITLEBAR_H

#include <QWidget>
#include <QToolButton>

#include "../interface/icallbacks.h"
#include "../ui/uimanager.h"


class QHBoxLayout;
class QLabel;

namespace pv {

class ITitleParent
{
public: 
    virtual void MoveWindow(int x, int y)=0;
    virtual QPoint GetParentPos()=0;
    virtual bool ParentIsMaxsized()=0;
    virtual void MoveBegin()=0;
    virtual void MoveEnd()=0;
};

namespace toolbars {

class TitleBar : public QWidget, public IUiWindow
{
    Q_OBJECT

public:
    TitleBar(bool top, QWidget *parent, ITitleParent *titleParent, bool hasClose);
    ~TitleBar();
    
    void setTitle(QString title); 
    QString title();

    //IUiWindow
    void UpdateLanguage() override;
    void UpdateTheme() override;
    void UpdateFont() override;

    inline void set_native(){
        _is_native = true;
    }

    inline void update_font(){
        UpdateFont();
    }

    void EnableAbleDrag(bool bEnabled);

private: 
    void reStyle();

    bool ParentIsMaxsized();

signals:
    void normalShow();
    void maximizedShow();

public slots:
    void showMaxRestore();
    void setRestoreButton(bool max);
    inline bool IsMoving(){return _moving;}

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
 
    
    QToolButton *_minimizeButton;
    QToolButton *_maximizeButton;
    QToolButton *_closeButton;
    QLabel      *_title;
  
    bool        _moving;
    bool        _is_draging;
    bool        _isTop;
    bool        _hasClose;
    QPoint      _clickPos;
    QPoint      _oldPos;
    QWidget     *_parent;
    bool        _is_native;
    ITitleParent    *_titleParent;
    bool        _is_done_moved;
    bool        _is_able_drag;
};

} // namespace toolbars
} // namespace pv

#endif // DSVIEW_PV_TOOLBARS_TITLEBAR_H
