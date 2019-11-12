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
  GtkBox  *forecast;
};

G_DEFINE_TYPE (WeatherWindow, weather_window, GTK_TYPE_APPLICATION_WINDOW)

static void
weather_window_class_init (WeatherWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/com/obyknovenius/Weather/weather-window.ui");
  gtk_widget_class_bind_template_child (widget_class, WeatherWindow, forecast);
}

static void
weather_window_init (WeatherWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  GtkBox *forecast = self->forecast;
  for (int i = 0; i < 10; i++)
    {
      GtkWidget *hour = g_object_new (WEATHER_TYPE_HOUR, NULL);
      gtk_box_pack_start (GTK_BOX (forecast), hour, FALSE, TRUE, 0);
      if (i < 9)
        {
          GtkWidget *separator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
          gtk_widget_set_visible (separator, TRUE);
          gtk_box_pack_start (GTK_BOX (forecast), separator, FALSE, TRUE, 0);
        }
    }
}
