weather_sources = [
  'main.c',
  'weather-window.c',
  'weather-hour.c',
]

weather_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

gnome = import('gnome')

weather_sources += gnome.compile_resources('weather-resources',
  'weather.gresource.xml',
  c_name: 'weather'
)

executable('weather', weather_sources,
  dependencies: weather_deps,
  install: true,
)
