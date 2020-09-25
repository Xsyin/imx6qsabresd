/*
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright NXP
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_DPAA2_IO_H
#define __FSL_DPAA2_IO_H

#include <linux/types.h>
#include <linux/cpumask.h>
#include <linux/irqreturn.h>

#include "dpaa2-fd.h"
#include "dpaa2-global.h"

struct dpaa2_io;
struct dpaa2_io_store;
struct device;

/**
 * DOC: DPIO Service
 *
 * The DPIO service provides APIs for users to interact with the datapath
 * by enqueueing and dequeing frame descriptors.
 *
 * The following set of APIs can be used to enqueue and dequeue frames
 * as well as producing notification callbacks when data is available
 * for dequeue.
 */

#define DPAA2_IO_ANY_CPU	-1

/**
 * struct dpaa2_io_desc - The DPIO descriptor
 * @receives_notifications: Use notificaton mode. Non-zero if the DPIO
 *                  has a channel.
 * @has_8prio:      Set to non-zero for channel with 8 priority WQs.  Ignored
 *                  unless receives_notification is TRUE.
 * @cpu:            The cpu index that at least interrupt handlers will
 *                  execute on.
 * @stash_affinity: The stash affinity for this portal favour 'cpu'
 * @regs_cena:      The cache enabled regs.
 * @regs_cinh:      The cache inhibited regs
 * @dpio_id:        The dpio index
 * @qman_version:   The qman version
 *
 * Describes the attributes and features of the DPIO object.
 */
struct dpaa2_io_desc {
	int receives_notifications;
	int has_8prio;
	int cpu;
	void *regs_cena;
	void *regs_cinh;
	int dpio_id;
	u32 qman_version;
};

struct dpaa2_io *dpaa2_io_create(const struct dpaa2_io_desc *desc);

void dpaa2_io_down(struct dpaa2_io *d);

irqreturn_t dpaa2_io_irq(struct dpaa2_io *obj);

/**
 * struct dpaa2_io_notification_ctx - The DPIO notification context structure
 * @cb:           The callback to be invoked when the notification arrives
 * @is_cdan:      Zero for FQDAN, non-zero for CDAN
 * @id:           FQID or channel ID, needed for rearm
 * @desired_cpu:  The cpu on which the notifications will show up. Use
 *                DPAA2_IO_ANY_CPU if don't care
 * @dpio_id:      The dpio index
 * @qman64:       The 64-bit context value shows up in the FQDAN/CDAN.
 * @node:         The list node
 * @dpio_private: The dpio object internal to dpio_service
 *
 * Used when a FQDAN/CDAN registration is made by drivers.
 */
struct dpaa2_io_notification_ctx {
	void (*cb)(struct dpaa2_io_notification_ctx *);
	int is_cdan;
	u32 id;
	int desired_cpu;
	int dpio_id;
	u64 qman64;
	struct list_head node;
	void *dpio_private;
};

int dpaa2_io_service_register(struct dpaa2_io *service,
			      struct dpaa2_io_notification_ctx *ctx);
void dpaa2_io_service_deregister(struct dpaa2_io *service,
				 struct dpaa2_io_notification_ctx *ctx);
int dpaa2_io_service_rearm(struct dpaa2_io *service,
			   struct dpaa2_io_notification_ctx *ctx);

int dpaa2_io_service_pull_fq(struct dpaa2_io *d, u32 fqid,
			     struct dpaa2_io_store *s);
int dpaa2_io_service_pull_channel(struct dpaa2_io *d, u32 channelid,
				  struct dpaa2_io_store *s);

int dpaa2_io_service_enqueue_fq(struct dpaa2_io *d, u32 fqid,
				const struct dpaa2_fd *fd);
int dpaa2_io_service_enqueue_qd(struct dpaa2_io *d, u32 qdid, u8 prio,
				u16 qdbin, const struct dpaa2_fd *fd);
int dpaa2_io_service_release(struct dpaa2_io *d, u32 bpid,
			     const u64 *buffers, unsigned int num_buffers);
int dpaa2_io_service_acquire(struct dpaa2_io *d, u32 bpid,
			     u64 *buffers, unsigned int num_buffers);

struct dpaa2_io_store *dpaa2_io_store_create(unsigned int max_frames,
					     struct device *dev);
void dpaa2_io_store_destroy(struct dpaa2_io_store *s);
struct dpaa2_dq *dpaa2_io_store_next(struct dpaa2_io_store *s, int *is_last);

#endif /* __FSL_DPAA2_IO_H */
