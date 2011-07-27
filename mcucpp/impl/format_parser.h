#pragma once
namespace IO
{
	template<class Stream, FormatMode Mode, class FormatStrPtrType>
	void FormatParser<Stream, Mode, FormatStrPtrType>::ProcessFormat()
	{
		if(_formatSrting)
		{
			while(true)
			{
			    if(*_formatSrting == '%')
			    {
			        _formatSrting++;
                    if(*_formatSrting != '%')
                    {
                        if(*_formatSrting == '|' && ScanFlags)
                        {
                            bool isFlag=true;
                            do{
                                _formatSrting++;
                                typename Stream::fmtflags flags, mask;

                                if(*_formatSrting == '+')
                                {
                                    mask = flags = Stream::showpos;
                                }
                                else if(*_formatSrting == '#')
                                {
                                    mask = flags = Stream::showbase | Stream::boolalpha;
                                }
                                else if(*_formatSrting == 'x')
                                {
                                    flags = Stream::hex;
                                    mask = Stream::basefield;
                                }
                                else if(*_formatSrting == 'o')
                                {
                                    flags = Stream::oct;
                                    mask = Stream::basefield;
                                }
                                else if(*_formatSrting == '0')
                                {
                                    out.fill('0');
                                    flags = Stream::right;
                                    mask = Stream::adjustfield;
                                }
                                else if(*_formatSrting == '-')
                                {
                                    out.fill(' ');
                                    flags = Stream::left;
                                    mask = Stream::adjustfield;
                                }
                                else
                                {
                                    isFlag = false;
                                }

                                if(isFlag)
                                {
                                    out.setf(flags, mask);
                                }
                            }while(isFlag);
                            if(ScanFieldWidth)
                            {
								unsigned width;
								_formatSrting += Impl::StringToIntDec<unsigned>(_formatSrting, width);
								out.width(width);
                            }
                            if(ScanFloatPrecision && *_formatSrting == '.')
                            {
                                _formatSrting++;
                                unsigned presc;
                                _formatSrting += Impl::StringToIntDec<unsigned>(_formatSrting, presc);
                                out.precision(presc);
                            }
                            if(*_formatSrting == '|')
                                _formatSrting++;
                        }
                    }
                    return;
                }
                if(*_formatSrting == '\0')
                {
                    _formatSrting = 0;
                    return;
                }
				out.put(*_formatSrting);
				_formatSrting++;
			}
		}
	}
}
