#include <stdbool.h>
#include <drawing_element.h>
#include <utils.h>
#include <SketchUpAPI/sketchup.h>

static VALUE Sketchup_DrawingElement_bounds(VALUE self)
{
	SUDrawingElementRef drawing_element = {DATA_PTR(self)};
	struct SUBoundingBox3D bbox;
	SUDrawingElementGetBoundingBox(drawing_element, &bbox);
	return Data_Wrap_Struct(rb_path2class(GEOM_BOUNDINGBOX), 0, 0, &bbox);
}

static VALUE Sketchup_DrawingElement_Get_casts_shadows(VALUE self)
{
	SUDrawingElementRef drawing_element = {DATA_PTR(self)};
	bool casts_shadows_flag = false;
	SUDrawingElementGetCastsShadows(drawing_element, &casts_shadows_flag);
	return casts_shadows_flag ? Qtrue : Qfalse;
}

static VALUE Sketchup_DrawingElement_Set_casts_shadows(VALUE self, VALUE casts_shadows_flag)
{
	SUDrawingElementRef drawing_element = {DATA_PTR(self)};
	enum SUResult result = SUDrawingElementSetCastsShadows(drawing_element, casts_shadows_flag);
	if(result != SU_ERROR_NONE)
		return Qnil;
	return casts_shadows_flag;
}

static VALUE Sketchup_DrawingElement_Get_receives_shadows(VALUE self)
{
	SUDrawingElementRef drawing_element = {DATA_PTR(self)};
	bool receives_shadows_flag = false;
	SUDrawingElementGetReceivesShadows(drawing_element, &receives_shadows_flag);
	return receives_shadows_flag ? Qtrue : Qfalse;
}

static VALUE Sketchup_DrawingElement_Set_receives_shadows(VALUE self, VALUE receives_shadows_flag)
{
	SUDrawingElementRef drawing_element = {DATA_PTR(self)};
	enum SUResult result = SUDrawingElementSetReceivesShadows(drawing_element, receives_shadows_flag);
	if(result != SU_ERROR_NONE)
		return Qnil;
	return receives_shadows_flag;
}

static VALUE Sketchup_DrawingElement_Get_hidden(VALUE self)
{
	SUDrawingElementRef drawing_element = {DATA_PTR(self)};
	bool hide_flag = false;
	SUDrawingElementGetHidden(drawing_element, &hide_flag);
	return hide_flag ? Qtrue : Qfalse;
}

static VALUE Sketchup_DrawingElement_Set_hidden(VALUE self, VALUE hide_flag)
{
	SUDrawingElementRef drawing_element = {DATA_PTR(self)};
	enum SUResult result = SUDrawingElementSetHidden(drawing_element, hide_flag);
	if(result != SU_ERROR_NONE)
		return Qnil;
	return hide_flag;
}

static VALUE Sketchup_DrawingElement_Get_visible(VALUE self)
{
	SUDrawingElementRef drawing_element = {DATA_PTR(self)};
	bool hide_flag = false;
	SUDrawingElementGetHidden(drawing_element, &hide_flag);
	return hide_flag ? Qfalse : Qtrue;
}

static VALUE Sketchup_DrawingElement_Set_visible(VALUE self, VALUE visible_flag)
{
	SUDrawingElementRef drawing_element = {DATA_PTR(self)};
	enum SUResult result = SUDrawingElementSetHidden(drawing_element, visible_flag);
	if(result != SU_ERROR_NONE)
		return Qnil;
	return visible_flag;
}

static VALUE Sketchup_DrawingElement_Get_material(VALUE self)
{
	SUDrawingElementRef drawing_element = {DATA_PTR(self)};
	SUMaterialRef material = SU_INVALID;
	SUDrawingElementGetMaterial(drawing_element, &material);
	return Data_Wrap_Struct(rb_path2class(SKETCHUP_MATERIAL), 0, 0, material.ptr);
}

static VALUE Sketchup_DrawingElement_Set_material(VALUE self, VALUE material)
{
	if (!rb_obj_is_kind_of(material, rb_path2class(SKETCHUP_MATERIAL)))
		rb_raise(rb_eTypeError, "Wrong type of object given");

	SUDrawingElementRef drawing_element = {DATA_PTR(self)};	
	SUMaterialRef drawing_element_material = {DATA_PTR(material)};
	SUDrawingElementSetMaterial(drawing_element, drawing_element_material);
	return material;
}

static VALUE Sketchup_DrawingElement_Get_layer(VALUE self)
{
	SUDrawingElementRef drawing_element = {DATA_PTR(self)};
	SULayerRef layer = SU_INVALID;
	SUDrawingElementGetLayer(drawing_element, &layer);
	return Data_Wrap_Struct(rb_path2class(SKETCHUP_LAYER), 0, 0, layer.ptr);
}

static VALUE Sketchup_DrawingElement_Set_layer(VALUE self, VALUE layer)
{
	if (!rb_obj_is_kind_of(layer, rb_path2class(SKETCHUP_LAYER)))
		rb_raise(rb_eArgError, "Wrong type of object given");

	SUDrawingElementRef drawing_element = {DATA_PTR(self)};	
	SULayerRef drawing_element_layer = {DATA_PTR(layer)};
	SUDrawingElementSetLayer(drawing_element, drawing_element_layer);
	return layer;
}

VALUE DrawingElement_Init(VALUE Sketchup, VALUE Sketchup_Entity)
{
	VALUE Sketchup_DrawingElement = rb_define_class_under(Sketchup, DRAWINGELEMENT, Sketchup_Entity);
	rb_undef_alloc_func(Sketchup_DrawingElement);
	rb_define_method(Sketchup_DrawingElement, "bounds", Sketchup_DrawingElement_bounds, 0);
	rb_define_method(Sketchup_DrawingElement, "casts_shadows?", Sketchup_DrawingElement_Get_casts_shadows, 0);
	rb_define_method(Sketchup_DrawingElement, "casts_shadows=", Sketchup_DrawingElement_Set_casts_shadows, 1);
	rb_define_method(Sketchup_DrawingElement, "receives_shadows?", Sketchup_DrawingElement_Get_receives_shadows, 0);
	rb_define_method(Sketchup_DrawingElement, "receives_shadows=", Sketchup_DrawingElement_Set_receives_shadows, 1);
	rb_define_method(Sketchup_DrawingElement, "hidden?", Sketchup_DrawingElement_Get_hidden, 0);
	rb_define_method(Sketchup_DrawingElement, "hidden=", Sketchup_DrawingElement_Set_hidden, 1);
	rb_define_method(Sketchup_DrawingElement, "visible?", Sketchup_DrawingElement_Get_visible, 0);
	rb_define_method(Sketchup_DrawingElement, "visible=", Sketchup_DrawingElement_Set_visible, 1);
	rb_define_method(Sketchup_DrawingElement, "material", Sketchup_DrawingElement_Get_material, 0);
	rb_define_method(Sketchup_DrawingElement, "material=", Sketchup_DrawingElement_Set_material, 1);
	rb_define_method(Sketchup_DrawingElement, "layer", Sketchup_DrawingElement_Get_layer, 0);
	rb_define_method(Sketchup_DrawingElement, "layer=", Sketchup_DrawingElement_Set_layer, 1);
	return Sketchup_DrawingElement;
}