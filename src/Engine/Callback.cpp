#include "Callback.h"


Callback::Callback ( PCALLBACK in_funcCallback, void *in_pExtra):
    m_funcCallback (in_funcCallback),
    m_pExtra (in_pExtra)
{}
Callback::Callback ( const Callback &in_Callback ):
    m_funcCallback (in_Callback.m_funcCallback),
    m_pExtra (in_Callback.m_pExtra)
{}
Callback &Callback::operator = ( const Callback &in_Callback )
{
	m_funcCallback = in_Callback.m_funcCallback;
	m_pExtra = in_Callback.m_pExtra;
	return *this;
}
