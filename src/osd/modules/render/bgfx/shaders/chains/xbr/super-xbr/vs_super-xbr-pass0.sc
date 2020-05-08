$input a_position, a_texcoord0, a_color0
$output v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3, v_texcoord4, v_color0

// license:MIT
// copyright-holders:Hyllian

/*
   
  *******  Super XBR Shader - pass0 vertex shader *******
   
  Copyright (c) 2016 Hyllian - sergiogdb@gmail.com

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

*/

#include "common.sh"

uniform vec4 u_tex_size0;

void main()
{
	gl_Position = mul(u_viewProj, vec4(a_position.xy, 0.0, 1.0));
	v_texcoord0 = a_texcoord0;

	vec2 ps = 1.0 / u_tex_size0.xy;
	float dx = ps.x;
	float dy = ps.y;
	v_texcoord1 = v_texcoord0.xyxy + vec4(-dx, -dy, 2.0*dx, 2.0*dy);
	v_texcoord2 = v_texcoord0.xyxy + vec4(0.0, -dy,     dx, 2.0*dy);
	v_texcoord3 = v_texcoord0.xyxy + vec4(-dx, 0.0, 2.0*dx,     dy);
	v_texcoord4 = v_texcoord0.xyxy + vec4(0.0, 0.0,     dx,     dy);
	v_color0 = a_color0;
}
