

#define FUNCTION_FUNCTION DAHUA_JOIN(TFunction,FUNCTION_NUMBER)

#if FUNCTION_NUMBER == 0
#  define FUNCTION_COMMA
#else
#  define FUNCTION_COMMA ,
#endif // FUNCTION_NUMBER > 0

#define SP_MEM_FUNCTION_INVOKER DAHUA_JOIN(sp_mem_function_invoker, FUNCTION_NUMBER)
#define MEM_FUNCTION_INVOKER DAHUA_JOIN(mem_function_invoker, FUNCTION_NUMBER)
#define GEN_FUNCTION_INVOKER DAHUA_JOIN(gen_function_invoker, FUNCTION_NUMBER)


template< bool > struct SP_MEM_FUNCTION_INVOKER
{
	template< FUNCTION_CLASS_TYPES > struct inner
	{
		template< class O, class F >
		static typename Detail::function_return_type<R>::type invoke(
			Memory::TSharedPtr<O>& o, F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
		{
			return (o.get()->*f)(FUNCTION_ARGS);
		}
	};
};

template<> struct SP_MEM_FUNCTION_INVOKER< true >
{
	template< FUNCTION_CLASS_TYPES > struct inner
	{
		template< class O, class F >
		static typename Detail::function_return_type<R>::type invoke(
			Memory::TSharedPtr<O>& o, F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
		{
			DAHUA_FUNCTION_RETURN( (o.get()->*f)(FUNCTION_ARGS) );
		}
	};
};

template< bool > struct MEM_FUNCTION_INVOKER
{
	template< FUNCTION_CLASS_TYPES > struct inner
	{
		template< class O, class F >
		static typename Detail::function_return_type<R>::type invoke(
			O* obj, F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
		{
			return (obj->*f)(FUNCTION_ARGS);
		}
	};
};

template<> struct MEM_FUNCTION_INVOKER< true >
{
	template< FUNCTION_CLASS_TYPES > struct inner
	{
		template< class O, class F >
		static typename Detail::function_return_type<R>::type invoke(
			O* obj, F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
		{
			DAHUA_FUNCTION_RETURN((obj->*f)(FUNCTION_ARGS)); 
		}
	};
};

template< bool > struct GEN_FUNCTION_INVOKER
{
	template< FUNCTION_CLASS_TYPES > struct inner
	{
		template< class F >
		static typename Detail::function_return_type<R>::type invoke(
			F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
		{
			return f(FUNCTION_ARGS);
		}
	};
};

template<> struct GEN_FUNCTION_INVOKER< true >
{
	template< FUNCTION_CLASS_TYPES > struct inner
	{
		template< class F >
		static typename Detail::function_return_type<R>::type invoke(
			F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
		{
			DAHUA_FUNCTION_RETURN( f(FUNCTION_ARGS) );
		}
	};
};

template <FUNCTION_CLASS_TYPES>
class FUNCTION_FUNCTION
{
	class X{};
	
	typedef R (X::*MEM_FUNCTION)(FUNCTION_TYPES);
	
	typedef R (*GEN_FUNCTION)(FUNCTION_TYPES);
	
	
	enum {
		MEMBER_SHAREDPTR_FUNC,
		MEMBER_OBJ_FUNC,
		GEN_FUNC,
		INVALID_FUNC
	};
	
	int m_type;
	
	union {
		MEM_FUNCTION memberFunc;
		GEN_FUNCTION genFunc;
	}m_f;
	X*                      m_obj;
	Memory::TSharedPtr< X > m_sptr;
	
public:
	
	/// 缺省构造函数
	FUNCTION_FUNCTION()
		: m_type(INVALID_FUNC)
		, m_obj(NULL)
	{
		m_f.memberFunc = NULL;
		m_f.genFunc	= NULL;
	}

	template< class T >
	FUNCTION_FUNCTION( R(T::*f)(FUNCTION_TYPES), Memory::TSharedPtr< T > const& object )
		: m_type(MEMBER_SHAREDPTR_FUNC)
		, m_obj(NULL)
		, m_sptr(object, Detail::horrible_cast<X*, T*>(object.get()))
	{
		m_f.memberFunc = Detail::horrible_cast<MEM_FUNCTION>(f);
	}

	
	template< class T >
	FUNCTION_FUNCTION( R(T::*f)(FUNCTION_TYPES), T* object )
		: m_type(MEMBER_OBJ_FUNC)
		, m_obj( Detail::horrible_cast<X*, T*>(object) )
	{
		m_f.memberFunc = Detail::horrible_cast<MEM_FUNCTION>(f);
	}
	
	FUNCTION_FUNCTION( R( *f )(FUNCTION_TYPES) )
		: m_type(GEN_FUNC)
		, m_obj(NULL)
	{
		m_f.genFunc = Detail::horrible_cast<GEN_FUNCTION>(f);
	}
	
	FUNCTION_FUNCTION( FUNCTION_FUNCTION const& rhs )
		: m_type(rhs.m_type)
		, m_obj(NULL)
	{
		if (MEMBER_SHAREDPTR_FUNC == m_type)
		{
			m_sptr = rhs.m_sptr;
			m_f.memberFunc = rhs.m_f.memberFunc;
		}
		else if (MEMBER_OBJ_FUNC == m_type)
		{
			m_obj = rhs.m_obj;
			m_f.memberFunc = rhs.m_f.memberFunc;
		}
		else if (GEN_FUNC == m_type)
		{
			m_f.genFunc = rhs.m_f.genFunc;
		}
	}
	
	FUNCTION_FUNCTION& operator=( FUNCTION_FUNCTION const& rhs )
	{
		if ( this != &rhs )
		{
			m_type = rhs.m_type;
			if (MEMBER_SHAREDPTR_FUNC == m_type)
			{
				m_sptr = rhs.m_sptr;
				m_f.memberFunc = rhs.m_f.memberFunc;
			}
			else if (MEMBER_OBJ_FUNC == m_type)
			{
				m_obj = rhs.m_obj;
				m_f.memberFunc = rhs.m_f.memberFunc;
			}
			else if (GEN_FUNC == m_type)
			{
				m_f.genFunc = rhs.m_f.genFunc;
			}
		}
		return *this;
	}
	
	bool operator==( FUNCTION_FUNCTION const& rhs )
	{
		if (MEMBER_SHAREDPTR_FUNC == m_type)
		{
			return (m_sptr.get() == rhs.m_sptr.get()) && (m_f.memberFunc == rhs.m_f.memberFunc);
		}
		else if (MEMBER_OBJ_FUNC == m_type)
		{
			return (m_obj == rhs.m_obj) && (m_f.memberFunc == rhs.m_f.memberFunc);
		}
		else if (GEN_FUNC == m_type)
		{
			return (m_f.genFunc == rhs.m_f.genFunc);
		}
		return false;
	}
	
	/// 用于有效性判断
	operator bool() const
	{
		if (MEMBER_SHAREDPTR_FUNC == m_type)
		{
			return NULL != m_f.memberFunc && 0 != m_sptr.use_count();
		}
		else if (MEMBER_OBJ_FUNC == m_type)
		{
			return NULL != m_f.memberFunc && NULL != m_obj;
		}
		else if (GEN_FUNC == m_type)
		{
			return NULL != m_f.genFunc;
		}
		return false;
	}
	
	inline typename Detail::function_return_type<R>::type operator()(FUNCTION_TYPE_ARGS)
	{
		if (MEMBER_SHAREDPTR_FUNC == m_type) 
		{
			typedef DAHUA_FUNCTION_TYPENAME SP_MEM_FUNCTION_INVOKER< Detail::is_void<R>::value 
				>::DAHUA_FUNCTION_TEMPLATE inner< R FUNCTION_COMMA FUNCTION_TYPES > Invoker;
			return Invoker::invoke(	m_sptr, m_f.memberFunc FUNCTION_COMMA FUNCTION_ARGS );
		}
		else if (MEMBER_OBJ_FUNC == m_type)
		{
			typedef DAHUA_FUNCTION_TYPENAME MEM_FUNCTION_INVOKER< Detail::is_void<R>::value 
				>::DAHUA_FUNCTION_TEMPLATE inner< R FUNCTION_COMMA FUNCTION_TYPES > Invoker;
			return Invoker::invoke( m_obj, m_f.memberFunc FUNCTION_COMMA FUNCTION_ARGS );
		}
		else if (GEN_FUNC == m_type)
		{
			typedef DAHUA_FUNCTION_TYPENAME GEN_FUNCTION_INVOKER< Detail::is_void<R>::value 
				>::DAHUA_FUNCTION_TEMPLATE inner< R FUNCTION_COMMA FUNCTION_TYPES > Invoker;
			return Invoker::invoke(m_f.genFunc FUNCTION_COMMA FUNCTION_ARGS);
		}
		else
		{
			throw -1;
		}
	}
};

#undef FUNCTION_FUNCTION
#undef FUNCTION_COMMA
#undef GEN_FUNCTION_INVOKER
#undef MEM_FUNCTION_INVOKER
#undef SP_MEM_FUNCTION_INVOKER


