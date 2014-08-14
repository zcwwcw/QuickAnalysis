#-------------------------------------------------
#
# Project created by QtCreator 2014-02-23T23:49:47
#
#-------------------------------------------------

QT       += core gui svg opengl

TARGET = qwt
TEMPLATE = lib

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    QT += printsupport
    QT += concurrent
}

SOURCES += \
    qwt_widget_overlay.cpp \
    qwt_wheel.cpp \
    qwt_transform.cpp \
    qwt_thermo.cpp \
    qwt_text_label.cpp \
    qwt_text_engine.cpp \
    qwt_text.cpp \
    qwt_system_clock.cpp \
    qwt_symbol.cpp \
    qwt_spline.cpp \
    qwt_slider.cpp \
    qwt_series_data.cpp \
    qwt_scale_widget.cpp \
    qwt_scale_map.cpp \
    qwt_scale_engine.cpp \
    qwt_scale_draw.cpp \
    qwt_scale_div.cpp \
    qwt_sampling_thread.cpp \
    qwt_round_scale_draw.cpp \
    qwt_raster_data.cpp \
    qwt_point_polar.cpp \
    qwt_point_mapper.cpp \
    qwt_point_data.cpp \
    qwt_point_3d.cpp \
    qwt_plot_zoomer.cpp \
    qwt_plot_zoneitem.cpp \
    qwt_plot_xml.cpp \
    qwt_plot_tradingcurve.cpp \
    qwt_plot_textlabel.cpp \
    qwt_plot_svgitem.cpp \
    qwt_plot_spectrogram.cpp \
    qwt_plot_spectrocurve.cpp \
    qwt_plot_shapeitem.cpp \
    qwt_plot_seriesitem.cpp \
    qwt_plot_scaleitem.cpp \
    qwt_plot_rescaler.cpp \
    qwt_plot_renderer.cpp \
    qwt_plot_rasteritem.cpp \
    qwt_plot_picker.cpp \
    qwt_plot_panner.cpp \
    qwt_plot_multi_barchart.cpp \
    qwt_plot_marker.cpp \
    qwt_plot_magnifier.cpp \
    qwt_plot_legenditem.cpp \
    qwt_plot_layout.cpp \
    qwt_plot_item.cpp \
    qwt_plot_intervalcurve.cpp \
    qwt_plot_histogram.cpp \
    qwt_plot_grid.cpp \
    qwt_plot_glcanvas.cpp \
    qwt_plot_directpainter.cpp \
    qwt_plot_dict.cpp \
    qwt_plot_curve.cpp \
    qwt_plot_canvas.cpp \
    qwt_plot_barchart.cpp \
    qwt_plot_axis.cpp \
    qwt_plot_abstract_barchart.cpp \
    qwt_plot.cpp \
    qwt_pixel_matrix.cpp \
    qwt_picker_machine.cpp \
    qwt_picker.cpp \
    qwt_panner.cpp \
    qwt_painter_command.cpp \
    qwt_painter.cpp \
    qwt_null_paintdevice.cpp \
    qwt_matrix_raster_data.cpp \
    qwt_math.cpp \
    qwt_magnifier.cpp \
    qwt_legend_label.cpp \
    qwt_legend_data.cpp \
    qwt_legend.cpp \
    qwt_knob.cpp \
    qwt_interval_symbol.cpp \
    qwt_interval.cpp \
    qwt_graphic.cpp \
    qwt_event_pattern.cpp \
    qwt_dyngrid_layout.cpp \
    qwt_dial_needle.cpp \
    qwt_dial.cpp \
    qwt_date_scale_engine.cpp \
    qwt_date_scale_draw.cpp \
    qwt_date.cpp \
    qwt_curve_fitter.cpp \
    qwt_counter.cpp \
    qwt_compass_rose.cpp \
    qwt_compass.cpp \
    qwt_column_symbol.cpp \
    qwt_color_map.cpp \
    qwt_clipper.cpp \
    qwt_arrow_button.cpp \
    qwt_analog_clock.cpp \
    qwt_abstract_slider.cpp \
    qwt_abstract_scale_draw.cpp \
    qwt_abstract_scale.cpp \
    qwt_abstract_legend.cpp

HEADERS += \
    qwt_widget_overlay.h \
    qwt_wheel.h \
    qwt_transform.h \
    qwt_thermo.h \
    qwt_text_label.h \
    qwt_text_engine.h \
    qwt_text.h \
    qwt_system_clock.h \
    qwt_symbol.h \
    qwt_spline.h \
    qwt_slider.h \
    qwt_series_store.h \
    qwt_series_data.h \
    qwt_scale_widget.h \
    qwt_scale_map.h \
    qwt_scale_engine.h \
    qwt_scale_draw.h \
    qwt_scale_div.h \
    qwt_sampling_thread.h \
    qwt_samples.h \
    qwt_round_scale_draw.h \
    qwt_raster_data.h \
    qwt_point_polar.h \
    qwt_point_mapper.h \
    qwt_point_data.h \
    qwt_point_3d.h \
    qwt_plot_zoomer.h \
    qwt_plot_zoneitem.h \
    qwt_plot_tradingcurve.h \
    qwt_plot_textlabel.h \
    qwt_plot_svgitem.h \
    qwt_plot_spectrogram.h \
    qwt_plot_spectrocurve.h \
    qwt_plot_shapeitem.h \
    qwt_plot_seriesitem.h \
    qwt_plot_scaleitem.h \
    qwt_plot_rescaler.h \
    qwt_plot_renderer.h \
    qwt_plot_rasteritem.h \
    qwt_plot_picker.h \
    qwt_plot_panner.h \
    qwt_plot_multi_barchart.h \
    qwt_plot_marker.h \
    qwt_plot_magnifier.h \
    qwt_plot_legenditem.h \
    qwt_plot_layout.h \
    qwt_plot_item.h \
    qwt_plot_intervalcurve.h \
    qwt_plot_histogram.h \
    qwt_plot_grid.h \
    qwt_plot_glcanvas.h \
    qwt_plot_directpainter.h \
    qwt_plot_dict.h \
    qwt_plot_curve.h \
    qwt_plot_canvas.h \
    qwt_plot_barchart.h \
    qwt_plot_abstract_barchart.h \
    qwt_plot.h \
    qwt_pixel_matrix.h \
    qwt_picker_machine.h \
    qwt_picker.h \
    qwt_panner.h \
    qwt_painter_command.h \
    qwt_painter.h \
    qwt_null_paintdevice.h \
    qwt_matrix_raster_data.h \
    qwt_math.h \
    qwt_magnifier.h \
    qwt_legend_label.h \
    qwt_legend_data.h \
    qwt_legend.h \
    qwt_knob.h \
    qwt_interval_symbol.h \
    qwt_interval.h \
    qwt_graphic.h \
    qwt_global.h \
    qwt_event_pattern.h \
    qwt_dyngrid_layout.h \
    qwt_dial_needle.h \
    qwt_dial.h \
    qwt_date_scale_engine.h \
    qwt_date_scale_draw.h \
    qwt_date.h \
    qwt_curve_fitter.h \
    qwt_counter.h \
    qwt_compat.h \
    qwt_compass_rose.h \
    qwt_compass.h \
    qwt_column_symbol.h \
    qwt_color_map.h \
    qwt_clipper.h \
    qwt_arrow_button.h \
    qwt_analog_clock.h \
    qwt_abstract_slider.h \
    qwt_abstract_scale_draw.h \
    qwt_abstract_scale.h \
    qwt_abstract_legend.h \
    qwt.h

CONFIG(debug, debug|release){
    DLLDESTDIR = $$PWD/../debug
    DESTDIR = $$PWD/../libs/debug
    OBJECTS_DIR = $$PWD/debug/obj
    MOC_DIR = $$PWD/debug/moc
    UI_DIR = $$PWD/debug/ui
    RCC_DIR = $$PWD/debug/rcc
}else{
    DLLDESTDIR = $$PWD/../debug
    DESTDIR = $$PWD/../libs/debug
    OBJECTS_DIR = $$PWD/release/obj
    MOC_DIR = $$PWD/release/moc
    UI_DIR = $$PWD/release/ui
    RCC_DIR = $$PWD/release/rcc
}
