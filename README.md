اسکی‌فا: ابزاری مشابه آراسته برای ساخت هنر اسکی از متن فارسی
---

**توجه!**: اسکی‌فا تحت توسعه است و هنوز به نگارش پایدار نرسیده است. بهتر است از جایگزین قدیمی‌تر آن یعنی [آراسته](https://github.com/ekm507/araste) استفاده کنید.

# هدف‌گذاری‌ها

هدف‌گذاری نگارش ۱:

- ساخت برنامه‌ای که بتواند متن راست‌به‌چپ را با استفاده از قلم‌های aff آراسته رندر کند.

هدف‌گذاری نگارش‌های بعدی:

- افزودن امکان نصب

# نیازمندی

برای کمپایل و اجرا:

```bash
$ g++ -std=c++23 main.cpp && ./a.out
```

با این دستور اجرا کنید و خروجی بگیرید:
```bash
$ ./a.out "نوشته"
```

![image](https://github.com/ekm507/asciifa/assets/13185969/9843f189-f6dc-4f8f-ac11-dc1b0eace818)

# برای انجام

ابزار اسکی‌فا تحت توسعه است و هنوز اشکال‌های زیادی دارد که ناپایدارش می‌کنند.  
برخی از موارد برای انجام اینجا هستند.
این‌ها ممکن است بخشی از هدف‌گذاری برای نگارش ۱ برنامه به شمار بیایند.

- پشتیبانی از نویسه‌های zwnj که به دلیل رفتار عجیب تابع getline حذف شده است.
- اسکی‌فا هنوز با بسیاری از قلم‌ها مشکل دارد.
- اسکی‌فا هنوز از گلیف‌های چندحرفی مثل «لا» یا سریا پشتیبانی نمی‌کند.
- اسکی‌فا باید در صورت مواجهه با نویسه‌های ناموجود در قلم رفتار مناسبی نشان دهد.
- پشتیبانی از متن‌های طولانی‌تر از یک خط
- پشتیبانی از متن دوسویه
- گرفتن اندازهٔ پایانه برای امکان رندر در بزرگ‌ترین سایز
- ساخت یک رابط خط فرمان با سوییچ‌های مختلف
- آزمایش برنامه با قلم‌های مشکل‌دار. برنامه باید در مواجهه با آن‌ها رفتار مناسبی نشان دهد.