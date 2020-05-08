// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
#ifndef MAME_VIDEO_K053250_H
#define MAME_VIDEO_K053250_H

#pragma once

//
//  Konami 053250 road generator
//


class k053250_device :  public device_t,
						public device_gfx_interface,
						public device_video_interface
{
public:
	template <typename T, typename U>
	k053250_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock, T &&palette_tag, U &&screen_tag, int offx, int offy)
		: k053250_device(mconfig, tag, owner, clock)
	{
		set_palette(std::forward<T>(palette_tag));
		set_screen(std::forward<U>(screen_tag));
		set_offsets(offx, offy);
	}
	k053250_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void set_offsets(int offx, int offy)
	{
		m_offx = offx;
		m_offy = offy;
	}

	DECLARE_READ16_MEMBER(reg_r);
	DECLARE_WRITE16_MEMBER(reg_w);
	DECLARE_READ16_MEMBER(ram_r);
	DECLARE_WRITE16_MEMBER(ram_w);
	DECLARE_READ16_MEMBER(rom_r);

	void draw( bitmap_rgb32 &bitmap, const rectangle &cliprect, int colorbase, int flags, bitmap_ind8 &priority_bitmap, int priority );

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// configuration
	int m_offx, m_offy;

	// internal state
	required_region_ptr<uint8_t> m_rom;
	std::vector<uint8_t> m_unpacked_rom;
	std::vector<uint16_t> m_ram;
	uint16_t *m_buffer[2];
	uint8_t m_regs[8];
	uint8_t m_page;
	int32_t m_frame;

	// internal helpers
	void unpack_nibbles();
	void dma(int limiter);
	static void pdraw_scanline32(bitmap_rgb32 &bitmap, const pen_t *pal_base, uint8_t *source,
									const rectangle &cliprect, int linepos, int scroll, int zoom,
									uint32_t clipmask, uint32_t wrapmask, uint32_t orientation, bitmap_ind8 &priority, uint8_t pri);
};

DECLARE_DEVICE_TYPE(K053250, k053250_device)

#endif // MAME_VIDEO_K053250_H
