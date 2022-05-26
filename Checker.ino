bool atoui(const char *in, unsigned long *out)
{
  const char *p;
  for (p = in; *p; p++)
    if (*p > '9' || *p < '0')
      return false;

  *out = strtoul(in, NULL, 10);
  return true;
}
