
#ifndef __DAHUA_SP_COUNTED_BASE_IMPL_HPP__
#define __DAHUA_SP_COUNTED_BASE_IMPL_HPP__

#include <Infra/AtomicCount.h>
#include <typeinfo> 

namespace Dahua{
namespace Memory{
namespace Detail{

	class sp_counted_base
	{
	private:
		sp_counted_base( sp_counted_base const & );
		sp_counted_base & operator= ( sp_counted_base const & );
	
		Infra::CAtomicCount use_count_;
		Infra::CAtomicCount weak_count_;
		
	public:
		sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
		{
		}

		virtual ~sp_counted_base() // nothrow
		{
		}
		
		virtual void dispose() = 0; // nothrow
		
		virtual void destroy() // nothrow
		{
			delete this;
		}
		
		virtual void* get_untyped_deleter() = 0;
		virtual void* get_deleter( std::type_info const& ti) = 0;
		
		void add_ref_copy()
		{
			++use_count_;
		}
		
		bool add_ref_lock() // true on success
		{
			for( ; ; )
			{
				long tmp = use_count_;
				if( tmp == 0 ) return false;
				if (++use_count_ == (tmp + 1)) return true;
			}
		}
		
		void release()
		{
			if( --use_count_ == 0)
			{
				dispose();
				weak_release();
			}
		}
		
		void weak_add_ref()
		{
			++weak_count_;
		}
		
		void weak_release() // nothrow
		{
			if(--weak_count_ == 0)
			{
				destroy();
			}
		}
		
		long use_count() const // nothrow
		{
			return use_count_;
		}
	};

} /// namespace Detail
} /// namespace Memory
} /// namespace Dahua

#endif /// __DAHUA_SP_COUNTED_BASE_IMPL_HPP__
