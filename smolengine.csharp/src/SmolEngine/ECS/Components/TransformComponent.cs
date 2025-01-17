﻿using System;
using System.Runtime.InteropServices;

namespace SmolEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct TransformComponent
    {
        private Vector3 _Positios;
        private Vector3 _Rotation;
        private Vector3 _Scale;
        unsafe private readonly uint* _Handler;

        public Vector3 Position
        {
            get
            {
                return _Positios;
            }
            set
            {
                _Positios = value;
                OnValueChanged();
            }
        }

        public Vector3 Rotation
        {
            get
            {
                return _Rotation;
            }
            set
            {
                _Rotation = value;
                OnValueChanged();
            }
        }

        public Vector3 Scale
        {
            get
            {
                return _Scale;
            }
            set
            {
                _Scale = value;
                OnValueChanged();
            }
        }

        public override string ToString()
        {
            return "Pos:" + _Positios.ToString() + " Rot:" + _Rotation.ToString() + " Scale:" + _Scale.ToString();
        }

        private void OnValueChanged()
        {
            unsafe
            {
                if (_Handler != null)
                    Utils.OnComponentUpdated(ref this, *_Handler);
            }
        }

    }
}
