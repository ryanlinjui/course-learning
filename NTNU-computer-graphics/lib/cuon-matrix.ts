/**
 * cuon-matrix.ts (c) 2024 Jacob Lin
 *
 * TypeScript version of cuon-matrix.js (c) 2012 kanda and matsuda
 */

export class Matrix4 {
	public elements: Float32Array;

	constructor(m?: Matrix4) {
		if (m) {
			this.elements = new Float32Array(m.elements);
		} else {
			this.elements = new Float32Array([1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1]);
		}
	}

	/**
	 * Set the matrix to the identity matrix.
	 */
	public setIdentity(): this {
		const e = this.elements;
		e[0] = 1;
		e[4] = 0;
		e[8] = 0;
		e[12] = 0;
		e[1] = 0;
		e[5] = 1;
		e[9] = 0;
		e[13] = 0;
		e[2] = 0;
		e[6] = 0;
		e[10] = 1;
		e[14] = 0;
		e[3] = 0;
		e[7] = 0;
		e[11] = 0;
		e[15] = 1;
		return this;
	}

	/**
	 * Copy matrix.
	 * @param src The source matrix.
	 * @return this
	 */
	public set(src: Matrix4): this {
		const s = src.elements;
		const d = this.elements;

		if (s === d) {
			return this;
		}
		for (let i = 0; i < 16; ++i) {
			d[i] = s[i];
		}

		return this;
	}

	/**
	 * Multiply the matrix from the right.
	 * @param other The multiply matrix
	 * @return this
	 */
	public concat(other: Matrix4): this {
		const e = this.elements;
		const a = this.elements;
		let b = other.elements;

		if (e === b) {
			b = new Float32Array(16);
			for (let i = 0; i < 16; ++i) {
				b[i] = e[i];
			}
		}

		for (let i = 0; i < 4; i++) {
			const ai0 = a[i];
			const ai1 = a[i + 4];
			const ai2 = a[i + 8];
			const ai3 = a[i + 12];
			e[i] = ai0 * b[0] + ai1 * b[1] + ai2 * b[2] + ai3 * b[3];
			e[i + 4] = ai0 * b[4] + ai1 * b[5] + ai2 * b[6] + ai3 * b[7];
			e[i + 8] = ai0 * b[8] + ai1 * b[9] + ai2 * b[10] + ai3 * b[11];
			e[i + 12] = ai0 * b[12] + ai1 * b[13] + ai2 * b[14] + ai3 * b[15];
		}

		return this;
	}

	public multiply(other: Matrix4): this {
		return this.concat(other);
	}

	/**
	 * Multiply the three-dimensional vector.
	 * @param pos  The multiply vector
	 * @return The result of multiplication(Float32Array)
	 */
	public multiplyVector3(pos: Vector3): Vector3 {
		const e = this.elements;
		const p = pos.elements;
		const v = new Vector3();
		const result = v.elements;

		result[0] = p[0] * e[0] + p[1] * e[4] + p[2] * e[8] + e[11];
		result[1] = p[0] * e[1] + p[1] * e[5] + p[2] * e[9] + e[12];
		result[2] = p[0] * e[2] + p[1] * e[6] + p[2] * e[10] + e[13];

		return v;
	}

	/**
	 * Multiply the four-dimensional vector.
	 * @param pos  The multiply vector
	 * @return The result of multiplication(Float32Array)
	 */
	public multiplyVector4(pos: Vector4): Vector4 {
		const e = this.elements;
		const p = pos.elements;
		const v = new Vector4();
		const result = v.elements;

		result[0] = p[0] * e[0] + p[1] * e[4] + p[2] * e[8] + p[3] * e[12];
		result[1] = p[0] * e[1] + p[1] * e[5] + p[2] * e[9] + p[3] * e[13];
		result[2] = p[0] * e[2] + p[1] * e[6] + p[2] * e[10] + p[3] * e[14];
		result[3] = p[0] * e[3] + p[1] * e[7] + p[2] * e[11] + p[3] * e[15];

		return v;
	}

	/**
	 * Set the transpose of the matrix.
	 * @return this
	 */
	public transpose(): this {
		const e = this.elements;
		let t: number;

		t = e[1];
		e[1] = e[4];
		e[4] = t;
		t = e[2];
		e[2] = e[8];
		e[8] = t;
		t = e[3];
		e[3] = e[12];
		e[12] = t;
		t = e[6];
		e[6] = e[9];
		e[9] = t;
		t = e[7];
		e[7] = e[13];
		e[13] = t;
		t = e[11];
		e[11] = e[14];
		e[14] = t;

		return this;
	}

	/**
	 * Set the inverse of the matrix.
	 * @param other The source matrix
	 * @return this
	 */
	public setInverseOf(other: Matrix4): this {
		const s = other.elements;
		const d = this.elements;
		const inv = new Float32Array(16);
		let det: number;

		inv[0] =
			s[5] * s[10] * s[15] -
			s[5] * s[11] * s[14] -
			s[9] * s[6] * s[15] +
			s[9] * s[7] * s[14] +
			s[13] * s[6] * s[11] -
			s[13] * s[7] * s[10];
		inv[4] =
			-s[4] * s[10] * s[15] +
			s[4] * s[11] * s[14] +
			s[8] * s[6] * s[15] -
			s[8] * s[7] * s[14] -
			s[12] * s[6] * s[11] +
			s[12] * s[7] * s[10];
		inv[8] =
			s[4] * s[9] * s[15] -
			s[4] * s[11] * s[13] -
			s[8] * s[5] * s[15] +
			s[8] * s[7] * s[13] +
			s[12] * s[5] * s[11] -
			s[12] * s[7] * s[9];
		inv[12] =
			-s[4] * s[9] * s[14] +
			s[4] * s[10] * s[13] +
			s[8] * s[5] * s[14] -
			s[8] * s[6] * s[13] -
			s[12] * s[5] * s[10] +
			s[12] * s[6] * s[9];

		inv[1] =
			-s[1] * s[10] * s[15] +
			s[1] * s[11] * s[14] +
			s[9] * s[2] * s[15] -
			s[9] * s[3] * s[14] -
			s[13] * s[2] * s[11] +
			s[13] * s[3] * s[10];
		inv[5] =
			s[0] * s[10] * s[15] -
			s[0] * s[11] * s[14] -
			s[8] * s[2] * s[15] +
			s[8] * s[3] * s[14] +
			s[12] * s[2] * s[11] -
			s[12] * s[3] * s[10];
		inv[9] =
			-s[0] * s[9] * s[15] +
			s[0] * s[11] * s[13] +
			s[8] * s[1] * s[15] -
			s[8] * s[3] * s[13] -
			s[12] * s[1] * s[11] +
			s[12] * s[3] * s[9];
		inv[13] =
			s[0] * s[9] * s[14] -
			s[0] * s[10] * s[13] -
			s[8] * s[1] * s[14] +
			s[8] * s[2] * s[13] +
			s[12] * s[1] * s[10] -
			s[12] * s[2] * s[9];

		inv[2] =
			s[1] * s[6] * s[15] -
			s[1] * s[7] * s[14] -
			s[5] * s[2] * s[15] +
			s[5] * s[3] * s[14] +
			s[13] * s[2] * s[7] -
			s[13] * s[3] * s[6];
		inv[6] =
			-s[0] * s[6] * s[15] +
			s[0] * s[7] * s[14] +
			s[4] * s[2] * s[15] -
			s[4] * s[3] * s[14] -
			s[12] * s[2] * s[7] +
			s[12] * s[3] * s[6];
		inv[10] =
			s[0] * s[5] * s[15] -
			s[0] * s[7] * s[13] -
			s[4] * s[1] * s[15] +
			s[4] * s[3] * s[13] +
			s[12] * s[1] * s[7] -
			s[12] * s[3] * s[5];
		inv[14] =
			-s[0] * s[5] * s[14] +
			s[0] * s[6] * s[13] +
			s[4] * s[1] * s[14] -
			s[4] * s[2] * s[13] -
			s[12] * s[1] * s[6] +
			s[12] * s[2] * s[5];

		inv[3] =
			-s[1] * s[6] * s[11] +
			s[1] * s[7] * s[10] +
			s[5] * s[2] * s[11] -
			s[5] * s[3] * s[10] -
			s[9] * s[2] * s[7] +
			s[9] * s[3] * s[6];
		inv[7] =
			s[0] * s[6] * s[11] -
			s[0] * s[7] * s[10] -
			s[4] * s[2] * s[11] +
			s[4] * s[3] * s[10] +
			s[8] * s[2] * s[7] -
			s[8] * s[3] * s[6];
		inv[11] =
			-s[0] * s[5] * s[11] +
			s[0] * s[7] * s[9] +
			s[4] * s[1] * s[11] -
			s[4] * s[3] * s[9] -
			s[8] * s[1] * s[7] +
			s[8] * s[3] * s[5];
		inv[15] =
			s[0] * s[5] * s[10] -
			s[0] * s[6] * s[9] -
			s[4] * s[1] * s[10] +
			s[4] * s[2] * s[9] +
			s[8] * s[1] * s[6] -
			s[8] * s[2] * s[5];

		det = s[0] * inv[0] + s[1] * inv[4] + s[2] * inv[8] + s[3] * inv[12];
		if (det === 0) {
			return this;
		}

		det = 1 / det;
		for (let i = 0; i < 16; i++) {
			d[i] = inv[i] * det;
		}

		return this;
	}

	/**
	 * Set the inverse of this matrix.
	 * @return this
	 */
	public invert(): this {
		return this.setInverseOf(this);
	}

	/**
	 * Set the orthographic projection matrix.
	 * @param left The coordinate of the left vertical clipping plane
	 * @param right The coordinate of the right vertical clipping plane
	 * @param bottom The coordinate of the bottom horizontal clipping plane
	 * @param top The coordinate of the top horizontal clipping plane
	 * @param near The distance to the near depth clipping plane
	 * @param far The distance to the far depth clipping plane
	 * @return this
	 */
	public setOrtho(
		left: number,
		right: number,
		bottom: number,
		top: number,
		near: number,
		far: number,
	): this {
		if (left === right || bottom === top || near === far) {
			throw new Error("null frustum");
		}

		const rw = 1 / (right - left);
		const rh = 1 / (top - bottom);
		const rd = 1 / (far - near);
		const e = this.elements;

		e[0] = 2 * rw;
		e[1] = 0;
		e[2] = 0;
		e[3] = 0;

		e[4] = 0;
		e[5] = 2 * rh;
		e[6] = 0;
		e[7] = 0;

		e[8] = 0;
		e[9] = 0;
		e[10] = -2 * rd;
		e[11] = 0;

		e[12] = -(right + left) * rw;
		e[13] = -(top + bottom) * rh;
		e[14] = -(far + near) * rd;
		e[15] = 1;

		return this;
	}

	/**
	 * Multiply the orthographic projection matrix from the right.
	 * @param left The coordinate of the left vertical clipping plane
	 * @param right The coordinate of the right vertical clipping plane
	 * @param bottom The coordinate of the bottom horizontal clipping plane
	 * @param top The coordinate of the top horizontal clipping plane
	 * @param near The distance to the near depth clipping plane
	 * @param far The distance to the far depth clipping plane
	 * @return this
	 */
	public ortho(
		left: number,
		right: number,
		bottom: number,
		top: number,
		near: number,
		far: number,
	): this {
		return this.concat(new Matrix4().setOrtho(left, right, bottom, top, near, far));
	}

	/**
	 * Set the perspective projection matrix.
	 * @param left The coordinate of the left vertical clipping plane
	 * @param right The coordinate of the right vertical clipping plane
	 * @param bottom The coordinate of the bottom horizontal clipping plane
	 * @param top The coordinate of the top horizontal clipping plane
	 * @param near The distance to the near depth clipping plane
	 * @param far The distance to the far depth clipping plane
	 */
	public setFrustum(
		left: number,
		right: number,
		bottom: number,
		top: number,
		near: number,
		far: number,
	): this {
		if (left === right || top === bottom || near === far) {
			throw new Error("null frustum");
		}
		if (near <= 0) {
			throw new Error("near <= 0");
		}
		if (far <= 0) {
			throw new Error("far <= 0");
		}

		const rw = 1 / (right - left);
		const rh = 1 / (top - bottom);
		const rd = 1 / (far - near);
		const e = this.elements;

		e[0] = 2 * near * rw;
		e[1] = 0;
		e[2] = 0;
		e[3] = 0;

		e[4] = 0;
		e[5] = 2 * near * rh;
		e[6] = 0;
		e[7] = 0;

		e[8] = (right + left) * rw;
		e[9] = (top + bottom) * rh;
		e[10] = -(far + near) * rd;
		e[11] = -1;

		e[12] = 0;
		e[13] = 0;
		e[14] = -2 * near * far * rd;
		e[15] = 0;

		return this;
	}

	/**
	 * Multiply the perspective projection matrix from the right.
	 * @param left The X coordinate of the left clipping plane on the near clipping plane
	 * @param right The X coordinate of the right clipping plane on the near clipping plane
	 * @param bottom The Y coordinate of the bottom clipping plane on the near clipping plane
	 * @param top The Y coordinate of the top clipping plane on the near clipping plane
	 * @param near The distance to the near clipping plane. Must be positive
	 * @param far The distance to the far clipping plane. Must be positive
	 * @return this
	 */
	public frustum(
		left: number,
		right: number,
		bottom: number,
		top: number,
		near: number,
		far: number,
	): this {
		return this.concat(new Matrix4().setFrustum(left, right, bottom, top, near, far));
	}

	/**
	 * Set the perspective projection matrix.
	 * @param fovy The vertical field of view [degree]
	 * @param aspect The aspect ratio of the field of view
	 * @param near The distance to the near depth clipping plane. Must be positive
	 * @param far The distance to the far depth clipping plane. Must be positive
	 * @return this
	 */
	public setPerspective(fovy: number, aspect: number, near: number, far: number): this {
		if (near === far || aspect === 0) {
			throw "null frustum";
		}
		if (near <= 0) {
			throw "near <= 0";
		}
		if (far <= 0) {
			throw "far <= 0";
		}

		fovy = (Math.PI * fovy) / 180 / 2;
		const s = Math.sin(fovy);
		if (s === 0) {
			throw "null frustum";
		}

		const rd = 1 / (far - near);
		const ct = Math.cos(fovy) / s;

		const e = this.elements;

		e[0] = ct / aspect;
		e[1] = 0;
		e[2] = 0;
		e[3] = 0;

		e[4] = 0;
		e[5] = ct;
		e[6] = 0;
		e[7] = 0;

		e[8] = 0;
		e[9] = 0;
		e[10] = -(far + near) * rd;
		e[11] = -1;

		e[12] = 0;
		e[13] = 0;
		e[14] = -2 * near * far * rd;
		e[15] = 0;

		return this;
	}

	/**
	 * Multiply the perspective projection matrix from the right.
	 * @param fovy The vertical field of view [degree]
	 * @param aspect The aspect ratio of the field of view
	 * @param near The distance to the near depth clipping plane. Must be positive
	 * @param far The distance to the far depth clipping plane. Must be positive
	 * @return this
	 */
	public perspective(fovy: number, aspect: number, near: number, far: number): this {
		return this.concat(new Matrix4().setPerspective(fovy, aspect, near, far));
	}

	public setScale(x: number, y: number, z: number): this {
		const e = this.elements;
		e[0] = x;
		e[4] = 0;
		e[8] = 0;
		e[12] = 0;
		e[1] = 0;
		e[5] = y;
		e[9] = 0;
		e[13] = 0;
		e[2] = 0;
		e[6] = 0;
		e[10] = z;
		e[14] = 0;
		e[3] = 0;
		e[7] = 0;
		e[11] = 0;
		e[15] = 1;
		return this;
	}

	public scale(x: number, y: number, z: number): this {
		const e = this.elements;
		e[0] *= x;
		e[4] *= y;
		e[8] *= z;
		e[1] *= x;
		e[5] *= y;
		e[9] *= z;
		e[2] *= x;
		e[6] *= y;
		e[10] *= z;
		e[3] *= x;
		e[7] *= y;
		e[11] *= z;
		return this;
	}

	public setTranslate(x: number, y: number, z: number): this {
		const e = this.elements;
		e[0] = 1;
		e[4] = 0;
		e[8] = 0;
		e[12] = x;
		e[1] = 0;
		e[5] = 1;
		e[9] = 0;
		e[13] = y;
		e[2] = 0;
		e[6] = 0;
		e[10] = 1;
		e[14] = z;
		e[3] = 0;
		e[7] = 0;
		e[11] = 0;
		e[15] = 1;
		return this;
	}

	public translate(x: number, y: number, z: number): this {
		const e = this.elements;
		e[12] += e[0] * x + e[4] * y + e[8] * z;
		e[13] += e[1] * x + e[5] * y + e[9] * z;
		e[14] += e[2] * x + e[6] * y + e[10] * z;
		e[15] += e[3] * x + e[7] * y + e[11] * z;
		return this;
	}

	/**
	 * Set the rotation matrix.
	 * The vector of rotation axis may not be normalized.
	 * @param angle The angle of rotation [degree]
	 * @param x The X coordinate of vector of rotation axis
	 * @param y The Y coordinate of vector of rotation axis
	 * @param z The Z coordinate of vector of rotation axis
	 * @return this
	 */
	public setRotate(angle: number, x: number, y: number, z: number): this {
		angle = (Math.PI * angle) / 180;
		const e = this.elements;

		let s = Math.sin(angle);
		const c = Math.cos(angle);

		if (0 !== x && 0 === y && 0 === z) {
			// Rotation around the X-axis
			if (x < 0) {
				s = -s;
			}
			e[0] = 1;
			e[4] = 0;
			e[8] = 0;
			e[12] = 0;
			e[1] = 0;
			e[5] = c;
			e[9] = -s;
			e[13] = 0;
			e[2] = 0;
			e[6] = s;
			e[10] = c;
			e[14] = 0;
			e[3] = 0;
			e[7] = 0;
			e[11] = 0;
			e[15] = 1;
		} else if (0 === x && 0 !== y && 0 === z) {
			// Rotation around the Y-axis
			if (y < 0) {
				s = -s;
			}
			e[0] = c;
			e[4] = 0;
			e[8] = s;
			e[12] = 0;
			e[1] = 0;
			e[5] = 1;
			e[9] = 0;
			e[13] = 0;
			e[2] = -s;
			e[6] = 0;
			e[10] = c;
			e[14] = 0;
			e[3] = 0;
			e[7] = 0;
			e[11] = 0;
			e[15] = 1;
		} else if (0 === x && 0 === y && 0 !== z) {
			// Rotation around the Z-axis
			if (z < 0) {
				s = -s;
			}
			e[0] = c;
			e[4] = -s;
			e[8] = 0;
			e[12] = 0;
			e[1] = s;
			e[5] = c;
			e[9] = 0;
			e[13] = 0;
			e[2] = 0;
			e[6] = 0;
			e[10] = 1;
			e[14] = 0;
			e[3] = 0;
			e[7] = 0;
			e[11] = 0;
			e[15] = 1;
		} else {
			// Rotation around the arbitrary axis
			const len = Math.sqrt(x * x + y * y + z * z);
			if (len !== 1) {
				const rlen = 1 / len;
				x *= rlen;
				y *= rlen;
				z *= rlen;
			}
			const nc = 1 - c;
			const xy = x * y;
			const yz = y * z;
			const zx = z * x;
			const xs = x * s;
			const ys = y * s;
			const zs = z * s;

			e[0] = x * x * nc + c;
			e[1] = xy * nc + zs;
			e[2] = zx * nc - ys;
			e[3] = 0;

			e[4] = xy * nc - zs;
			e[5] = y * y * nc + c;
			e[6] = yz * nc + xs;
			e[7] = 0;

			e[8] = zx * nc + ys;
			e[9] = yz * nc - xs;
			e[10] = z * z * nc + c;
			e[11] = 0;

			e[12] = 0;
			e[13] = 0;
			e[14] = 0;
			e[15] = 1;
		}

		return this;
	}

	/**
	 * Multiply the matrix for rotation from the right.
	 * The vector of rotation axis may not be normalized.
	 * @param angle The angle of rotation [degree]
	 * @param x The X coordinate of vector of rotation axis
	 * @param y The Y coordinate of vector of rotation axis
	 * @param z The Z coordinate of vector of rotation axis
	 * @return this
	 */
	public rotate(angle: number, x: number, y: number, z: number): this {
		return this.concat(new Matrix4().setRotate(angle, x, y, z));
	}

	public setLookAt(
		eyeX: number,
		eyeY: number,
		eyeZ: number,
		centerX: number,
		centerY: number,
		centerZ: number,
		upX: number,
		upY: number,
		upZ: number,
	): this {
		const e = this.elements;

		let fx = centerX - eyeX;
		let fy = centerY - eyeY;
		let fz = centerZ - eyeZ;

		const rlf = 1 / Math.sqrt(fx * fx + fy * fy + fz * fz);
		fx *= rlf;
		fy *= rlf;
		fz *= rlf;

		let sx = fy * upZ - fz * upY;
		let sy = fz * upX - fx * upZ;
		let sz = fx * upY - fy * upX;

		const rls = 1 / Math.sqrt(sx * sx + sy * sy + sz * sz);
		sx *= rls;
		sy *= rls;
		sz *= rls;

		const ux = sy * fz - sz * fy;
		const uy = sz * fx - sx * fz;
		const uz = sx * fy - sy * fx;

		e[0] = sx;
		e[1] = ux;
		e[2] = -fx;
		e[3] = 0;

		e[4] = sy;
		e[5] = uy;
		e[6] = -fy;
		e[7] = 0;

		e[8] = sz;
		e[9] = uz;
		e[10] = -fz;
		e[11] = 0;

		e[12] = 0;
		e[13] = 0;
		e[14] = 0;
		e[15] = 1;

		return this.translate(-eyeX, -eyeY, -eyeZ);
	}

	/**
	 * Multiply the view matrix from the right.
	 * @param eyeX, eyeY, eyeZ The position of the eye point
	 * @param centerX, centerY, centerZ The position of the reference point
	 * @param upX, upY, upZ The direction of the up vector
	 * @return this
	 */
	public lookAt(
		eyeX: number,
		eyeY: number,
		eyeZ: number,
		centerX: number,
		centerY: number,
		centerZ: number,
		upX: number,
		upY: number,
		upZ: number,
	): this {
		return this.concat(
			new Matrix4().setLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ),
		);
	}

	public dropShadow(plane: number[], light: number[]): this {
		const e = this.elements;
		const dot =
			plane[0] * light[0] + plane[1] * light[1] + plane[2] * light[2] + plane[3] * light[3];

		e[0] = dot - light[0] * plane[0];
		e[1] = -light[1] * plane[0];
		e[2] = -light[2] * plane[0];
		e[3] = -light[3] * plane[0];

		e[4] = -light[0] * plane[1];
		e[5] = dot - light[1] * plane[1];
		e[6] = -light[2] * plane[1];
		e[7] = -light[3] * plane[1];

		e[8] = -light[0] * plane[2];
		e[9] = -light[1] * plane[2];
		e[10] = dot - light[2] * plane[2];
		e[11] = -light[3] * plane[2];

		e[12] = -light[0] * plane[3];
		e[13] = -light[1] * plane[3];
		e[14] = -light[2] * plane[3];
		e[15] = dot - light[3] * plane[3];

		return this.concat(new Matrix4());
	}

	public dropShadowDirectionally(
		normX: number,
		normY: number,
		normZ: number,
		planeX: number,
		planeY: number,
		planeZ: number,
		lightX: number,
		lightY: number,
		lightZ: number,
	): this {
		const a = planeX * normX + planeY * normY + planeZ * normZ;
		return this.dropShadow([normX, normY, normZ, -a], [lightX, lightY, lightZ, 0]);
	}
}

export class Vector3 {
	public elements: Float32Array;

	constructor(src?: Float32Array | number[]) {
		this.elements = new Float32Array(3);
		if (src) {
			this.elements[0] = src[0];
			this.elements[1] = src[1];
			this.elements[2] = src[2];
		}
	}

	public normalize(): this {
		const v = this.elements;
		const c = v[0],
			d = v[1],
			e = v[2];
		let g = Math.sqrt(c * c + d * d + e * e);
		if (g) {
			if (g == 1) return this;
		} else {
			v[0] = 0;
			v[1] = 0;
			v[2] = 0;
			return this;
		}
		g = 1 / g;
		v[0] = c * g;
		v[1] = d * g;
		v[2] = e * g;
		return this;
	}
}

export class Vector4 {
	public elements: Float32Array;

	constructor(src?: Float32Array | number[]) {
		this.elements = new Float32Array(4);
		if (src) {
			this.elements[0] = src[0];
			this.elements[1] = src[1];
			this.elements[2] = src[2];
			this.elements[3] = src[3];
		}
	}
}
