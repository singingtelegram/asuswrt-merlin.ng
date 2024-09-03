#include "cmdlist_arch.h"
#include "cmdlist.h"
#include "rdp_mm.h"

#if !defined(RDP_ARCH_SIM)
#error "non sim compilation"
#endif

void *cmdlist_buffer_alloc(phys_addr_t *phys_addr_p)
{
    bdmf_phys_addr_t phys_addr;
    void *buffer_p = rdp_mm_aligned_alloc_atomic(CMDLIST_BUFFER_SIZE, &phys_addr);

    if(buffer_p)
    {
        *phys_addr_p = (phys_addr_t)phys_addr;
    }

    __logDebug("buffer_p %p, phys_addr %px", buffer_p, (void *)*phys_addr_p);

    return buffer_p;
}

void cmdlist_buffer_free(void *buffer_p)
{
    __logDebug("buffer_p %px", buffer_p);

    rdp_mm_aligned_free(buffer_p, CMDLIST_BUFFER_SIZE);
}

void cmdlist_buffer_flush(void *buffer_p)
{
}

int cmdlist_buffer_construct() { return 0; }
void cmdlist_buffer_destruct() {}
