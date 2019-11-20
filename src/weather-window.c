/* weather-window.c
 *
 * Copyright 2019 Vitaly Dyackhov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "weather-config.h"
#include "weather-window.h"
#include "weather-hour.h"

struct _WeatherWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkBox         *box;
};

G_DEFINE_TYPE (WeatherWindow, weather_window, GTK_TYPE_APPLICATION_WINDOW)

gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
  guint width, height;
  guint top_padding = 80, bottom_padding = 40;

  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);

  cairo_set_source_rgb(cr, 209.0 / 255.0, 148.0 / 255.0, 12.0 / 255.0);
  cairo_set_line_width(cr, 4);

  cairo_move_to(cr, 0, top_padding + ((1 - 0.2) * (height - top_padding - bottom_padding)));
  cairo_line_to(cr, 0.1 * width - 40, top_padding + ((1 - 0.2) * (height - top_padding - bottom_padding)));
  cairo_line_to(cr, 0.2 * width - 40, top_padding + ((1 - 0.5) * (height - top_padding - bottom_padding)));
  cairo_line_to(cr, 0.3 * width - 40, top_padding + ((1 - 0.5) * (height - top_padding - bottom_padding)));
  cairo_line_to(cr, 0.4 * width - 40, top_padding + ((1 - 0.3) * (height - top_padding - bottom_padding)));
  cairo_line_to(cr, 0.5 * width - 40, top_padding + ((1 - 0.3) * (height - top_padding - bottom_padding)));
  cairo_line_to(cr, 0.6 * width - 40, top_padding + ((1 - 0.4) * (height - top_padding - bottom_padding)));
  cairo_line_to(cr, 0.7 * width - 40, top_padding + ((1 - 0.7) * (height - top_padding - bottom_padding)));
  cairo_line_to(cr, 0.8 * width - 40, top_padding + ((1 - 0.7) * (height - top_padding - bottom_padding)));
  cairo_line_to(cr, 0.9 * width - 40, top_padding + ((1 - 0.4) * (height - top_padding - bottom_padding)));
  cairo_line_to(cr, width, top_padding+ ((1 - 0.4) * (height - top_padding)));
  cairo_stroke_preserve (cr);

  cairo_line_to(cr, width, height);
  cairo_line_to(cr, 0, height);

  cairo_set_source_rgb(cr, 238.0 / 255.0, 214.0 / 255.0, 127.0 / 255.0);
  cairo_fill(cr);

  return FALSE;
}

static void
weather_window_class_init (WeatherWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/com/obyknovenius/Weather/weather-window.ui");
  gtk_widget_class_bind_template_child (widget_class, WeatherWindow, box);
}

static void
weather_window_init (WeatherWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  g_signal_connect(self->box, "draw", G_CALLBACK(draw), NULL);

  GtkBox *box = self->box;
  for (int i = 0; i < 10; i++)
    {
      GtkWidget *hour = g_object_new (WEATHER_TYPE_HOUR, NULL);
      gtk_box_pack_start (GTK_BOX (box), hour, FALSE, TRUE, 0);
      if (i < 9)
        {
          GtkWidget *separator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
          gtk_widget_set_visible (separator, TRUE);
          gtk_box_pack_start (GTK_BOX (box), separator, FALSE, TRUE, 0);
        }
    }
}
