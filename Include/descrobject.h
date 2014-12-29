/* Descriptors */
#ifndef Py_DESCROBJECT_H
#define Py_DESCROBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

typedef PyObject *(*getter)(PyObject *, void *);
typedef int (*setter)(PyObject *, PyObject *, void *);

typedef struct PyGetSetDef {
	char *name;
	getter get;
	setter set;
	char *doc;
	void *closure;
} PyGetSetDef;

typedef PyObject *(*wrapperfunc)(PyObject *self, PyObject *args,
				 void *wrapped);

typedef PyObject *(*wrapperfunc_kwds)(PyObject *self, PyObject *args,
				      void *wrapped, PyObject *kwds);

struct wrapperbase {
	char *name;		// __add__
	int offset;		// function的偏移, 也即PyWrapperDescrObject->d_wrapped指向的函数的偏移.
	// 接下来四个字段怎么用?
	// 两个函数对象, 区别是?
	void *function;	
	wrapperfunc wrapper;
	char *doc;
	int flags;
	PyObject *name_strobj;	// 转成内部可索引的string-object
};

/* Flags for above struct */
#define PyWrapperFlag_KEYWORDS 1 /* wrapper function takes keyword args */

/* Various kinds of descriptor objects */
// d_type指向包裹的函数所属的type object
// 这几种descriptor各有什么用?
#define PyDescr_COMMON \
	PyObject_HEAD \
	PyTypeObject *d_type; \
	PyObject *d_name

typedef struct {
	PyDescr_COMMON;
} PyDescrObject;

typedef struct {
	PyDescr_COMMON;
	PyMethodDef *d_method;
} PyMethodDescrObject;

typedef struct {
	PyDescr_COMMON;
	struct PyMemberDef *d_member;
} PyMemberDescrObject;

typedef struct {
	PyDescr_COMMON;
	PyGetSetDef *d_getset;
} PyGetSetDescrObject;

typedef struct {
	PyDescr_COMMON;
	struct wrapperbase *d_base;	// 指向的slot对象
	void *d_wrapped; /* This can be any function pointer */	// type_object里的函数指针
} PyWrapperDescrObject;

PyAPI_DATA(PyTypeObject) PyWrapperDescr_Type;

PyAPI_FUNC(PyObject *) PyDescr_NewMethod(PyTypeObject *, PyMethodDef *);
PyAPI_FUNC(PyObject *) PyDescr_NewClassMethod(PyTypeObject *, PyMethodDef *);
PyAPI_FUNC(PyObject *) PyDescr_NewMember(PyTypeObject *,
					       struct PyMemberDef *);
PyAPI_FUNC(PyObject *) PyDescr_NewGetSet(PyTypeObject *,
					       struct PyGetSetDef *);
PyAPI_FUNC(PyObject *) PyDescr_NewWrapper(PyTypeObject *,
						struct wrapperbase *, void *);
#define PyDescr_IsData(d) ((d)->ob_type->tp_descr_set != NULL)

PyAPI_FUNC(PyObject *) PyDictProxy_New(PyObject *);
PyAPI_FUNC(PyObject *) PyWrapper_New(PyObject *, PyObject *);


PyAPI_DATA(PyTypeObject) PyProperty_Type;
#ifdef __cplusplus
}
#endif
#endif /* !Py_DESCROBJECT_H */

