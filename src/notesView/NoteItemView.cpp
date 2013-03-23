/*
 * File:   NoteItemView.cpp
 * Author: piotr
 *
 * Created on June 25, 2012, 8:45 PM
 */

#include "Resources.h"
#include "NoteItemView.h"

namespace note
{

ItemView::ItemView()
{
    _isSelected = false;
}

ItemView::~ItemView()
{
}

void ItemView::on_realize()
{
    Gtk::Widget::on_realize();

    fontTime.set_family(Resources::res->fontName);
    fontTime.set_weight(Pango::WEIGHT_NORMAL);

    fontTitle.set_family(Resources::res->fontName);
    fontTitle.set_weight(Pango::WEIGHT_ULTRALIGHT);

    fontDescription.set_family(Resources::res->fontName);
    fontDescription.set_weight(Pango::WEIGHT_ULTRALIGHT);

    this->add_events(Gdk::BUTTON_PRESS_MASK);
    this->add_events(Gdk::BUTTON_RELEASE_MASK);

    this->set_can_focus(true);

    set_size_request(-1, HEIGHT);
    set_margin_bottom(SPACE);
}

void ItemView::setData(ItemData data)
{
    this->data = data;
}

ItemData& ItemView::getData()
{
    return data;
}

void ItemView::setSelected(bool value)
{
    _isSelected = value;
    this->queue_draw();
}

bool ItemView::isSelected()
{
    return _isSelected;
}

bool ItemView::isHit(GdkEventButton* event, Gdk::Rectangle& rect)
{
    const int left = rect.get_x();
    const int top = rect.get_y();
    const int right = left + rect.get_width();
    const int bottom = top + rect.get_height();

    if (event->x > left && event->x < right)
        if (event->y > top && event->y < bottom)
            return true;

    return false;}

bool ItemView::on_button_release_event(GdkEventButton* event)
{
    if (isHit(event, rectClearNotification))
    {
        signal_item_button_clicked.emit(this, (int)BUTTON_ID_TOGGLE_NOTIFICATION);
        return true;
    }

    if (isSelected())
    {
        //test buttons
        if (isHit(event, rectBtnDelete))
        {
            signal_item_button_clicked.emit(this, (int)BUTTON_ID_DELETE);
        }
        else if (isHit(event, rectBtnEdit))
        {
            signal_item_button_clicked.emit(this, (int)BUTTON_ID_EDIT);
        }
        else
        {
            signal_item_selected.emit(this);
        }
    }
    else
    {
        signal_item_selected.emit(this);
    }

    return true;
}

bool ItemView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();

    int width = allocation.get_width();
    int height = allocation.get_height();

    //draw bottom shadow
    cr->set_source_rgb(0.9, 0.9, 0.9);
    cr->paint();

    //make room for content
    height -= 1;

    //update clear notification button layout
    updateClearNotificationButtonLayout(width, height);

    fontTime.set_size(FONT_SIZE * PANGO_SCALE);
    fontTitle.set_size(FONT_SIZE * PANGO_SCALE);
    fontDescription.set_size(FONT_SIZE_SMALL * PANGO_SCALE);

    cr->set_antialias(Cairo::ANTIALIAS_NONE);

    drawBackground(cr, width, height);

    cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);

    //draw objects
    drawTime(cr, width, height);
    drawTitle(cr, width, height);
    drawDescription(cr, width, height);
    drawReminderIcon(cr, width, height);

    //update buttons layout according to selection state and description position
    updateButtonsLayout(width, height, rectDescription.get_y(), rectDescription.get_height());

    //draw buttons
    drawButtons(cr, width, height);

    return true;
}

ItemView::ColorMode ItemView::getColorMode()
{
    if (data.isReminder() && data.isNotification())
    {
        if (data.isNotificationCleared())
        {
            return COLOR_OK;
        }
        else
        {
            return COLOR_ALARM;
        }
    }

    return COLOR_INACTIVE;
}

void ItemView::drawInnerShadow(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height)
{
    cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);

    const int SIZE = height * 0.1;
    const double ALPHA = 0.2;
    const int x = TIME_WIDTH - SIZE;
    const int y = 0;

    Cairo::RefPtr<Cairo::LinearGradient> linearGradient = Cairo::LinearGradient::create(x, y, x + SIZE, y);
    linearGradient->add_color_stop_rgba(0, 0.00, 0.00, 0.00, 0.0);
    linearGradient->add_color_stop_rgba(1, 0.00, 0.00, 0.00, ALPHA);

    cr->set_source(linearGradient);
    cr->rectangle(x, y, SIZE, height);
    cr->fill();
}

void ItemView::drawBackground(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height)
{
    //fill background
    if (isSelected())
    {
        cr->set_source_rgb(1, 1, 1);
        cr->rectangle(0, 0, width, height);
        cr->fill();
    }
    else
    {
        cr->set_source_rgb(0.98, 0.98, 0.98);
        cr->rectangle(0, 0, width, height);
        cr->fill();
    }

    //time area
    Cairo::RefPtr<Cairo::LinearGradient> linearGradientTime = Cairo::LinearGradient::create(0, 0, 0, height);

    //set color by status
    ColorMode colorMode = getColorMode();

    if (colorMode == COLOR_INACTIVE)
    {
        //gray
        linearGradientTime->add_color_stop_rgb(0, 0.75, 0.75, 0.75);
        linearGradientTime->add_color_stop_rgb(1, 0.65, 0.65, 0.65);
    }

    if (colorMode == COLOR_ALARM)
    {
        //orange
        linearGradientTime->add_color_stop_rgb(0, 1.00, 0.60, 0.30);
        linearGradientTime->add_color_stop_rgb(1, 0.90, 0.50, 0.20);
    }

    if (colorMode == COLOR_OK)
    {
        //green
        linearGradientTime->add_color_stop_rgb(0, 0.40, 0.70, 0.45);
        linearGradientTime->add_color_stop_rgb(1, 0.30, 0.60, 0.35);
    }

    cr->set_source(linearGradientTime);
    cr->rectangle(0, 0, TIME_WIDTH, height);
    cr->fill();

    if (isSelected())
        drawInnerShadow(cr, width, height);
}

void ItemView::drawTime(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height)
{
    int text_width;
    int text_height;

    Glib::RefPtr<Pango::Layout> layTime = Pango::Layout::create(cr);
    layTime->set_font_description(fontTime);
    layTime->set_text(data.getTimeText());
    layTime->get_pixel_size(text_width, text_height);

    rectTime.set_x((TIME_WIDTH * 0.5) - (text_width * 0.5));
    rectTime.set_y((int)PADDING);
    rectTime.set_width(text_width);
    rectTime.set_height(text_height);

    //highlight
    const int highlightSize = 1;

    cr->move_to(rectTime.get_x(), rectTime.get_y() - highlightSize);

    //set colors
    ColorMode colorMode = getColorMode();

    if (colorMode == COLOR_INACTIVE)
    {
        //gray
        cr->set_source_rgb(0.6, 0.6, 0.6);
    }

    if (colorMode == COLOR_ALARM)
    {
        //orange
        cr->set_source_rgb(0.8, 0.40, 0.0);
    }

    if (colorMode == COLOR_OK)
    {
        //green
        cr->set_source_rgb(0.0, 0.55, 0.0);
    }

    layTime->show_in_cairo_context(cr);

    //inner color
    cr->move_to(rectTime.get_x(), rectTime.get_y());
    cr->set_source_rgb(1.0, 1.0, 1.0);
    layTime->show_in_cairo_context(cr);
}

void ItemView::drawTitle(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height)
{
    int text_width;
    int text_height;

    Glib::RefPtr<Pango::Layout> layTitle = Pango::Layout::create(cr);
    layTitle->set_font_description(fontTitle);
    layTitle->set_text(data.getTitle());
    layTitle->get_pixel_size(text_width, text_height);

    rectTitle.set_x(PADDING + TIME_WIDTH);
    rectTitle.set_y((int)PADDING);
    rectTitle.set_width(width - TIME_WIDTH - PADDING - SPACE);
    rectTitle.set_height(text_height);

    cr->move_to(rectTitle.get_x(), rectTitle.get_y());
    cr->set_source_rgb(0.2, 0.2, 0.2);

    layTitle->set_width(rectTitle.get_width() * PANGO_SCALE);
    layTitle->set_ellipsize(Pango::ELLIPSIZE_END);
    layTitle->set_single_paragraph_mode(true);
    layTitle->show_in_cairo_context(cr);
}

void ItemView::drawDescription(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height)
{
    //reference vertical position for later use
    int firstBaseline = rectTitle.get_y() + rectTitle.get_height() + PADDING;

    int text_width;
    int text_height;

    Glib::RefPtr<Pango::Layout> layDescription = Pango::Layout::create(cr);
    layDescription->set_font_description(fontDescription);
    layDescription->set_text(data.getDetails());
    layDescription->get_pixel_size(text_width, text_height);

    rectDescription.set_x(PADDING + TIME_WIDTH + SPACE);
    rectDescription.set_y(firstBaseline);
    rectDescription.set_width(width - TIME_WIDTH - getAllButtonsWidth() - (PADDING * 2));
    rectDescription.set_height(height - firstBaseline - PADDING);

    cr->move_to(rectDescription.get_x(), rectDescription.get_y());
    cr->set_source_rgb(0.4, 0.4, 0.4);

    layDescription->set_width(rectDescription.get_width() * PANGO_SCALE);
    layDescription->set_height(rectDescription.get_height() * PANGO_SCALE);
    layDescription->set_wrap(Pango::WRAP_WORD);
    layDescription->set_ellipsize(Pango::ELLIPSIZE_END);

    layDescription->set_single_paragraph_mode(false);
    layDescription->show_in_cairo_context(cr);
}

void ItemView::drawReminderIcon(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height)
{
    cr->save();

    //draw reminder icon
    cr->set_antialias(Cairo::ANTIALIAS_NONE);

    if (data.isReminder())
    {
        Gtk::Image* image = Resources::res->imgReminderIcon;

        if (getColorMode() == COLOR_ALARM)
            image = Resources::res->imgReminderOnIcon;

        const Glib::RefPtr<Gdk::Pixbuf> icon = image->get_pixbuf();

        const int iconLeft = (TIME_WIDTH * 0.5) - (icon->get_width() * 0.5);
        const int iconTop = (height - icon->get_height()) - (PADDING * 3);

        Gdk::Cairo::set_source_pixbuf(cr, icon, iconLeft, iconTop);

        cr->rectangle(iconLeft, iconTop, icon->get_width(), icon->get_height());
        cr->fill();
    }

    cr->restore();
}

void ItemView::updateClearNotificationButtonLayout(const int width, const int height)
{
    rectClearNotification.set_x(0);
    rectClearNotification.set_y(0);
    rectClearNotification.set_width((int)TIME_WIDTH);
    rectClearNotification.set_height(height);
}

void ItemView::updateButtonsLayout(const int width, const int height, const int containerTop, const int containerHeight)
{
    int btnLeft = width - getAllButtonsWidth();

    int btnTop = containerTop;
    int btnHeight = containerHeight;

    //int btnTop = rectDescription.get_y();
    //int btnHeight = rectDescription.get_height();

    rectBtnDelete.set_x(btnLeft);
    rectBtnDelete.set_y(btnTop);
    rectBtnDelete.set_width((int)BTN_WIDTH);
    rectBtnDelete.set_height(btnHeight);

    btnLeft += (BTN_WIDTH + PADDING);

    rectBtnEdit.set_x(btnLeft);
    rectBtnEdit.set_y(btnTop);
    rectBtnEdit.set_width((int)BTN_WIDTH);
    rectBtnEdit.set_height(btnHeight);
}

int ItemView::getAllButtonsWidth()
{
    if (isSelected())
        return (BTN_WIDTH + PADDING) * 2;

    return 0;
}

void ItemView::drawButton(const Cairo::RefPtr<Cairo::Context>& cr, Gtk::Image* image, Gdk::Rectangle rect)
{
    const Glib::RefPtr<Gdk::Pixbuf> icon = image->get_pixbuf();

    const int iconLeft = rect.get_x() + (rect.get_width() * 0.5) - (icon->get_width() * 0.5);
    const int iconTop = rect.get_y() + (rect.get_height() * 0.5) - (icon->get_height() * 0.5);

    Gdk::Cairo::set_source_pixbuf(cr, icon, iconLeft, iconTop);
    cr->rectangle(iconLeft, iconTop, icon->get_width(), icon->get_height());
    cr->fill();
}

void ItemView::drawButtons(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height)
{
    cr->save();

    cr->set_antialias(Cairo::ANTIALIAS_NONE);

    if (isSelected())
    {
        drawButton(cr, Resources::res->imgBtnDelete, rectBtnDelete);
        drawButton(cr, Resources::res->imgBtnEdit, rectBtnEdit);
    }

    cr->restore();
}

//note
};
